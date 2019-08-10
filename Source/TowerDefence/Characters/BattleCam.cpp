// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleCam.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"

// Sets default values
ABattleCam::ABattleCam()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera
	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
}

// Called when the game starts or when spawned
void ABattleCam::BeginPlay()
{
	Super::BeginPlay();
	
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
}

void ABattleCam::MoveForward(float Value)
{
	FVector NewLOC;
	FVector AsLOC; //assist location

	//moves camera forward & backward
	AsLOC = FVector(0.f, GetActorForwardVector().Z * (Value * 25.f), 0.f);
	NewLOC = FVector(GetActorLocation().X + AsLOC.X, 
	FMath::Clamp(GetActorLocation().Y, -9517.f, -4826.f) + AsLOC.Y, 
	GetActorLocation().Z + AsLOC.Z);

	SetActorLocation(NewLOC);
}

void ABattleCam::MoveRight(float Value)
{
	FVector NewLOC;
	FVector AsLOC; //assist location

	//gets Right vector
	AsLOC = GetActorRightVector() * (Value * 25.f);
	NewLOC = FVector(FMath::Clamp(GetActorLocation().X, -1655.f, 1339.f) + AsLOC.X, GetActorLocation().Y + AsLOC.Y, GetActorLocation().Z + AsLOC.Z);

	SetActorLocation(NewLOC);
}

FHitResult ABattleCam::RayLine()
{
	//start and end locations
	Start = GetActorLocation();
	End = Start + (GetActorForwardVector() * 1500.f);

	//create trace parameters for Line casting
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;
	FHitResult HitRes(ForceInit); //Re-initialize hit info

								  //call GetWorld() from within an actor extending class
	GetWorld()->LineTraceSingleByChannel(HitRes, Start, End, ECC_Camera, TraceParams);

	return FHitResult(HitRes);
}
