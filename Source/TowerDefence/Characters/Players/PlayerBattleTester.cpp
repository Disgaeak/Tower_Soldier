// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBattleTester.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerBattleTester::APlayerBattleTester()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.2f;

	HP = 7;
	Atk = 5;
	Def = 1;
	AtkSpd = 2.f;
}

void APlayerBattleTester::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerBattleTester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
