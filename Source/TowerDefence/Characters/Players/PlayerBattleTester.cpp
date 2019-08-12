// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBattleTester.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UMG/Public/Components/WidgetComponent.h"

APlayerBattleTester::APlayerBattleTester()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//sets default Lv 1 stats
	Lv = 1;
	HP = 7;
	MaxHP = 7;
	Atk = 5;
	Def = 1;
	AtkSpd = 2.f;
	XP = 0;
	maxXP = 15;

	//create HP widget
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI health"));
	HealthBar->SetupAttachment(RootComponent);
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBar->SetDrawSize(FVector2D(200.f, 60.f));
}

void APlayerBattleTester::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerBattleTester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
