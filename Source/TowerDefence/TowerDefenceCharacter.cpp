// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TowerDefenceCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Characters/NPCInterface.h"

//////////////////////////////////////////////////////////////////////////
// ATowerDefenceCharacter

ATowerDefenceCharacter::ATowerDefenceCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 400.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATowerDefenceCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Talk", IE_Pressed, this, &ATowerDefenceCharacter::Interact);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATowerDefenceCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATowerDefenceCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATowerDefenceCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATowerDefenceCharacter::LookUpAtRate);
}

void ATowerDefenceCharacter::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<APlayerController>(GetController());
	if (PC != nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Yay"))
}

void ATowerDefenceCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATowerDefenceCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATowerDefenceCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATowerDefenceCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ATowerDefenceCharacter::Battle()
{
	if (BatCam != nullptr)
	{
		GetWorld()->GetFirstPlayerController()->Possess(BatCam);
	}
}

FHitResult ATowerDefenceCharacter::Rayline()
{
	//start and end locations
	FVector StartPoint = GetActorLocation();
	FVector EndPoint = StartPoint + (GetActorForwardVector() * 300.f);

	//create trace parameters for Line casting
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;
	FHitResult HitRes(ForceInit); //Re-initialize hit info

	//call GetWorld() from within an actor extending class
	GetWorld()->LineTraceSingleByChannel(HitRes, StartPoint, EndPoint, ECC_Camera, TraceParams);

	return HitRes;
}

void ATowerDefenceCharacter::Interact()
{
	FName HitTag;

	//checks to see if actor is valid and initiate dialogue
	if (Rayline().GetActor() != NULL && Rayline().GetActor()->Tags.Num() > 0)
	{
		INPCInterface* Target = Cast<INPCInterface>(Rayline().GetActor());

		if (Target != nullptr)
		{
			Target->dialogue();
			//GetCharacterMovement()->MaxWalkSpeed = 0.f;
			PC->bShowMouseCursor = true;
			DisableInput(PC);
		}
	}
}