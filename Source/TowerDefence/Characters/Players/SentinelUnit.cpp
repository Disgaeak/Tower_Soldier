// Fill out your copyright notice in the Description page of Project Settings.


#include "SentinelUnit.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UMG/Public/Components/WidgetComponent.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "../../TowerDefenceGameMode.h"

ASentinelUnit::ASentinelUnit()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//sets default Lv 1 stats
	Lv = 1;
	HP = 18;
	MaxHP = 18;
	Atk = 3;
	Def = 4;
	AtkSpd = 2.5f;
	XP = 0;
	maxXP = Lv * Lv * Lv + 14;
	Tier = 1;
	classNam = EClassName::Guard;
	jobNam = EJobName::TownGuard;

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

void ASentinelUnit::BeginPlay()
{
	if (GetWorld()->GetAuthGameMode()) { GM = Cast<ATowerDefenceGameMode>(GetWorld()->GetAuthGameMode()); }
	if (GM->PlayerStats[3].Lv > 1)
	{
		Lv = GM->PlayerStats[3].Lv;
		HP = GM->PlayerStats[3].HP;
		MaxHP = GM->PlayerStats[3].MaxHP;
		Atk = GM->PlayerStats[3].Atk;
		Def = GM->PlayerStats[3].Def;
		AtkSpd = GM->PlayerStats[3].AtkSpd;
		XP = GM->PlayerStats[3].XP;
		maxXP = GM->PlayerStats[3].maxXP;
		Tier = GM->PlayerStats[3].Tier;
	}
	else
	{
		GM->PlayerStats[3].Lv = Lv;
		GM->PlayerStats[3].HP = HP;
		GM->PlayerStats[3].MaxHP = MaxHP;
		GM->PlayerStats[3].Atk = Atk;
		GM->PlayerStats[3].Def = Def;
		GM->PlayerStats[3].AtkSpd = AtkSpd;
		GM->PlayerStats[3].XP = XP;
		GM->PlayerStats[3].maxXP = maxXP;
		GM->PlayerStats[3].Tier = Tier;
	}

	UIChange();
}

void ASentinelUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASentinelUnit::GainXP(int32 EXP)
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

void ASentinelUnit::GetAllStats(int32 &Lvl, int32 &AHp, int32 &AmaxHP, int32 &AAtk, int32 &ADef, int32 &AXP, int32 &AmaxXP, uint8 &jobnum)
{
	Lvl = Lv; AHp = HP; AmaxHP = MaxHP; AAtk = Atk; ADef = Def; AXP = XP; AmaxXP = maxXP; jobnum = 2;
}

void ASentinelUnit::RangeOverlap(AActor * Other)
{
	if (Other != nullptr && Other->ActorHasTag(FName("Enemy")))
	{
		if (!bCanAttack)
		{
			bCanAttack = true;
			if (!GetWorld()->GetTimerManager().IsTimerActive(AtkHandle))
				GetWorld()->GetTimerManager().SetTimer(AtkHandle, this, &ASentinelUnit::StartAtkDmg, AtkSpd, true, 0.3);

			EnemyTarg = Cast<IBattleInterface>(Other);
		}
	}
}

void ASentinelUnit::EndAtkTime()
{
	bCanAttack = false;
	GetWorld()->GetTimerManager().ClearTimer(AtkHandle);
}

void ASentinelUnit::LevelUp()
{
	Lv++;
	switch (Tier)
	{
	case 1:
		MaxHP += FMath::RandRange(7, 11);
		Atk += FMath::RandRange(1, 2);
		Def += FMath::RandRange(2, 3);
		break;
	case 2:
		MaxHP += FMath::RandRange(11, 15);
		Atk += FMath::RandRange(2, 4);
		Def += FMath::RandRange(4, 6);
		break;
	case 3:
		MaxHP += FMath::RandRange(19, 24);
		Atk += FMath::RandRange(7, 10);
		Def += FMath::RandRange(11, 14);
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

	GM->PlayerStats[3].Lv = Lv;
	GM->PlayerStats[3].HP = HP;
	GM->PlayerStats[3].MaxHP = MaxHP;
	GM->PlayerStats[3].Atk = Atk;
	GM->PlayerStats[3].Def = Def;
	GM->PlayerStats[3].AtkSpd = AtkSpd;
	GM->PlayerStats[3].XP = XP;
	GM->PlayerStats[3].maxXP = maxXP;
	GM->PlayerStats[3].Tier = Tier;

	UIChange();
}

void ASentinelUnit::StartAtkDmg()
{
	int32 curDamage = (Atk + Lv) * 2;
	EnemyTarg->AtkDamage(curDamage);
}