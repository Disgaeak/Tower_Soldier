// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleCam.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "../WidgetControl.h"
#include "../TowerDefenceGameMode.h"
#include "../TowerDefenceCharacter.h"

// Sets default values
ABattleCam::ABattleCam()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera
	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	Cam->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABattleCam::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetWorld()->GetAuthGameMode()) { GM = Cast<ATowerDefenceGameMode>(GetWorld()->GetAuthGameMode()); }
}

// Called every frame
void ABattleCam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABattleCam::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABattleCam::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABattleCam::MoveRight);
	PlayerInputComponent->BindAction("BattleAction", IE_Pressed, this, &ABattleCam::Point);
	PlayerInputComponent->BindAction("BattleCancel", IE_Pressed, this, &ABattleCam::Cancel);
}

void ABattleCam::Point()
{
	//Spawns soldier to mouse location
	if (SelSoldier != nullptr)
	{
		APawn* Spawnd = GetWorld()->SpawnActor<APawn>(SelSoldier);
		FVector LOC = RayLine().Location;
		LOC.Z = LOC.Z + 100.f;
		Spawnd->SetActorLocation(LOC);
		Spawnd->SpawnDefaultController();
		Spawnd->Tags.Add(FName("Ally"));
	}
}

void ABattleCam::Cancel()
{
	//Resets selected soldier to nothing
	if(SelSoldier != nullptr)
		SelSoldier = NULL;
}

void ABattleCam::MoveForward(float Value)
{
	FVector NewLOC;
	FVector AsLOC; //assist location

	//moves camera forward & backward
	AsLOC = FVector(0.f, GetActorForwardVector().Z * (Value * 25.f), 0.f);

	switch (GM->GetStage())
	{
	case 0:
		NewLOC = FVector(GetActorLocation().X + AsLOC.X, FMath::Clamp(GetActorLocation().Y, -9517.f, -4826.f) + AsLOC.Y, GetActorLocation().Z + AsLOC.Z);
		break;
	case 1:
		NewLOC = FVector(GetActorLocation().X + AsLOC.X, FMath::Clamp(GetActorLocation().Y, -10380.f, -5277.f) + AsLOC.Y, GetActorLocation().Z + AsLOC.Z);
		break;
	default:
		break;
	}
	
	SetActorLocation(NewLOC);
}

void ABattleCam::MoveRight(float Value)
{
	FVector NewLOC;
	FVector AsLOC; //assist location

	//gets Right vector
	AsLOC = GetActorRightVector() * (Value * 25.f);
	switch (GM->GetStage())
	{
	case 0:
		NewLOC = FVector(FMath::Clamp(GetActorLocation().X, -1655.f, 1339.f) + AsLOC.X, GetActorLocation().Y + AsLOC.Y, GetActorLocation().Z + AsLOC.Z);
		break;
	case 1:
		NewLOC = FVector(FMath::Clamp(GetActorLocation().X, -1928.f, 1871.f) + AsLOC.X, GetActorLocation().Y + AsLOC.Y, GetActorLocation().Z + AsLOC.Z);
		break;
	default:
		break;
	}
	

	SetActorLocation(NewLOC);
}

FHitResult ABattleCam::RayLine()
{
	FVector WorldDir;
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC != nullptr)
	{
		PC->DeprojectMousePositionToWorld(Start, WorldDir);
	}
	//set start location
	End = Start + (WorldDir * 3000.f);

	//create trace parameters for Line casting
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;
	FHitResult HitRes(ForceInit); //Re-initialize hit info

	//call GetWorld() from within an actor extending class
	GetWorld()->LineTraceSingleByChannel(HitRes, Start, End, ECC_Camera, TraceParams);

	return FHitResult(HitRes);
}

void ABattleCam::SelectedPawn(TSubclassOf<APawn> Soldier)
{
	SelSoldier = Soldier;
}

void ABattleCam::OpenMenu()
{
	if (widCon != nullptr)
	{
		widCon->AddToViewport();
	}
}

void ABattleCam::endBattleSwitch()
{
	widCon->RemoveFromParent();
	GetWorld()->GetFirstPlayerController()->Possess(hubChara);

	ATowerDefenceCharacter* playChara = Cast<ATowerDefenceCharacter>(hubChara);
	playChara->enableCharaInput();

	//get rid of any remaining Ally
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Ally"), numofPlayers);
	for (int i = 0; i < numofPlayers.Num(); i++)
	{
		numofPlayers[i]->Destroy();
	}

	numofPlayers.Empty();

	//get rid of previous stage 
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Land"), numofPlayers);
	for (int i = 0; i < numofPlayers.Num(); i++)
	{
		numofPlayers[i]->Destroy();
	}

	numofPlayers.Empty();
}