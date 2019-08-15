// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBattleTester.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UMG/Public/Components/WidgetComponent.h"
#include "BattleInterface.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"

APlayerBattleTester::APlayerBattleTester()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//sets default Lv 1 stats
	Lv = 1;
	HP = 15;
	MaxHP = 15;
	Atk = 4;
	Def = 3;
	AtkSpd = 2.f;
	XP = 0;
	maxXP = Lv * Lv * Lv + 14;
	Tier = 1;
	classNam = EClassName::Soldier;

	//create HP widget
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI health"));
	HealthBar->SetupAttachment(RootComponent);
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBar->SetDrawSize(FVector2D(200.f, 60.f));

	//create box collider
	Atkrange = CreateDefaultSubobject<UBoxComponent>(TEXT("Range"));
	Atkrange->SetupAttachment(RootComponent);
	Atkrange->SetBoxExtent(FVector(70.f, 32.f, 32.f));
}

void APlayerBattleTester::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerBattleTester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerBattleTester::LevelUp()
{
	Lv++;
	switch (Tier)
	{
	case 1:
		MaxHP += FMath::RandRange(3, 6);
		Atk += FMath::RandRange(1, 3);
		Def += FMath::RandRange(1, 2);
		break;
	case 2:
		MaxHP += FMath::RandRange(10, 14);
		Atk += FMath::RandRange(4, 6);
		Def += FMath::RandRange(4, 6);
		break;
	case 3:
		MaxHP += FMath::RandRange(16, 20);
		Atk += FMath::RandRange(12, 15);
		Def += FMath::RandRange(8, 11);
		break;
	default:
		break;
	}
	
	HP = MaxHP;
	maxXP = Lv * Lv * Lv + 14;

	if (Lv == 30)
	{
		MaxHP += 5;
		HP = MaxHP;
		Atk += 3;
		Def += 3;
		AtkSpd = 2.3;
		Tier = 2;
		classNam = EClassName::Knight;
	}
	if (Lv == 60)
	{
		MaxHP += 10;
		HP = MaxHP;
		Atk += 6;
		Def += 5;
		AtkSpd = 2.7;
		Tier = 3;
		classNam = EClassName::General;
	}
}

void APlayerBattleTester::GainXP(int32 EXP)
{
	int32 usedXp = EXP;
	// gainXP to level up
	do
	{
		if (usedXp >= maxXP)
		{
			maxXP -= usedXp;
			LevelUp();
		}
		else
		{
			XP = usedXp;
			usedXp = 0;
		}

	} while (usedXp > 0);
}

void APlayerBattleTester::RangeOverlap(AActor* Other)
{
	if (Other != nullptr && Other->ActorHasTag(FName("Enemy")))
	{
		bCanAttack = true;
		if(!GetWorld()->GetTimerManager().IsTimerActive(AtkHandle))
			GetWorld()->GetTimerManager().SetTimer(AtkHandle, this, &APlayerBattleTester::StartAtkDmg, AtkSpd, true, 0.3);

		EnemyTarg = Cast<IBattleInterface>(Other);
	}
}

void APlayerBattleTester::StartAtkDmg()
{
	int32 curDamage = (Atk + Lv) * 2;
	EnemyTarg->AtkDamage(curDamage);
}

void APlayerBattleTester::EndAtkTime()
{
	bCanAttack = false;
	GetWorld()->GetTimerManager().ClearTimer(AtkHandle);
}