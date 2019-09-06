// Fill out your copyright notice in the Description page of Project Settings.


#include "KlaineUnit.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UMG/Public/Components/WidgetComponent.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "../../TowerDefenceGameMode.h"

AKlaineUnit::AKlaineUnit()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//sets default Lv 3 stats
	Lv = 3;
	HP = 38;
	MaxHP = 38;
	Atk = 6;
	Def = 9;
	AtkSpd = 2.3f;
	XP = 0;
	maxXP = Lv * Lv * Lv + 14;
	Tier = 1;
	classNam = EClassName::Guard;
	jobNam = EJobName::Hero;

	//create HP widget
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI health"));
	HealthBar->SetupAttachment(RootComponent);
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBar->SetDrawSize(FVector2D(200.f, 60.f));

	//create box collider
	Atkrange = CreateDefaultSubobject<UBoxComponent>(TEXT("Range"));
	Atkrange->SetupAttachment(RootComponent);
	Atkrange->SetBoxExtent(FVector(70.f, 32.f, 32.f));

	Tags.Add(FName("Ally"));
}

void AKlaineUnit::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->GetAuthGameMode()) { GM = Cast<ATowerDefenceGameMode>(GetWorld()->GetAuthGameMode()); }
	if (GM->PlayerStats[2].Lv > 3)
	{
		Lv = GM->PlayerStats[2].Lv;
		HP = GM->PlayerStats[2].HP;
		MaxHP = GM->PlayerStats[2].MaxHP;
		Atk = GM->PlayerStats[2].Atk;
		Def = GM->PlayerStats[2].Def;
		AtkSpd = GM->PlayerStats[2].AtkSpd;
		XP = GM->PlayerStats[2].XP;
		maxXP = GM->PlayerStats[2].maxXP;
		Tier = GM->PlayerStats[2].Tier;
	}
	else
	{
		GM->PlayerStats[2].Lv = Lv;
		GM->PlayerStats[2].HP = HP;
		GM->PlayerStats[2].MaxHP = MaxHP;
		GM->PlayerStats[2].Atk = Atk;
		GM->PlayerStats[2].Def = Def;
		GM->PlayerStats[2].AtkSpd = AtkSpd;
		GM->PlayerStats[2].XP = XP;
		GM->PlayerStats[2].maxXP = maxXP;
		GM->PlayerStats[2].Tier = Tier;
	}

	UIChange();
}

void AKlaineUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKlaineUnit::LevelUp()
{
	Lv++;
	switch (Tier)
	{
	case 1:
		MaxHP += FMath::RandRange(8, 12);
		Atk += FMath::RandRange(1, 2);
		Def += FMath::RandRange(1, 3);
		break;
	case 2:
		MaxHP += FMath::RandRange(12, 16);
		Atk += FMath::RandRange(3, 5);
		Def += FMath::RandRange(4, 7);
		break;
	case 3:
		MaxHP += FMath::RandRange(20, 25);
		Atk += FMath::RandRange(8, 11);
		Def += FMath::RandRange(12, 15);
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
		AtkSpd = 2.0;
		Tier = 2;
		classNam = EClassName::Sentinel;
	}
	if (Lv == 60)
	{
		MaxHP += 10;
		HP = MaxHP;
		Atk += 6;
		Def += 5;
		AtkSpd = 1.5;
		Tier = 3;
		classNam = EClassName::Guardian;
	}

	GM->PlayerStats[2].Lv = Lv;
	GM->PlayerStats[2].HP = HP;
	GM->PlayerStats[2].MaxHP = MaxHP;
	GM->PlayerStats[2].Atk = Atk;
	GM->PlayerStats[2].Def = Def;
	GM->PlayerStats[2].AtkSpd = AtkSpd;
	GM->PlayerStats[2].XP = XP;
	GM->PlayerStats[2].maxXP = maxXP;
	GM->PlayerStats[2].Tier = Tier;

	UIChange();
}

void AKlaineUnit::StartAtkDmg()
{
	int32 curDamage = (Atk + Lv) * 2;
	EnemyTarg->AtkDamage(curDamage);
}

void AKlaineUnit::GainXP(int32 EXP)
{
	int32 usedXp = EXP;
	// gainXP to level up
	do
	{
		if (usedXp >= maxXP)
		{
			usedXp -= maxXP;
			LevelUp();

		}
		else
		{
			XP = usedXp;
			usedXp = 0;
		}

	} while (usedXp > 0);
}

void AKlaineUnit::GetAllStats(int32 &Lvl, int32 &AHp, int32 &AmaxHP, int32 &AAtk, int32 &ADef, int32 &AXP, int32 &AmaxXP, uint8 &jobnum)
{
	Lvl = Lv; AHp = HP; AmaxHP = MaxHP; AAtk = Atk; ADef = Def; AXP = XP; AmaxXP = maxXP; jobnum = 2;
}

void AKlaineUnit::RangeOverlap(AActor *Other)
{
	if (Other != nullptr && Other->ActorHasTag(FName("Enemy")))
	{
		if (!bCanAttack)
		{
			bCanAttack = true;
			if (!GetWorld()->GetTimerManager().IsTimerActive(AtkHandle))
				GetWorld()->GetTimerManager().SetTimer(AtkHandle, this, &AKlaineUnit::StartAtkDmg, AtkSpd, true, 0.3);

			EnemyTarg = Cast<IBattleInterface>(Other);
		}
	}
}

void AKlaineUnit::EndAtkTime()
{
	bCanAttack = false;
	GetWorld()->GetTimerManager().ClearTimer(AtkHandle);
}