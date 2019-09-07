// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBattleTester.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UMG/Public/Components/WidgetComponent.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "../../TowerDefenceGameMode.h"

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

void APlayerBattleTester::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->GetAuthGameMode()) { GM = Cast<ATowerDefenceGameMode>(GetWorld()->GetAuthGameMode()); }
	if (GM->PlayerStats[0].Lv > 1)
	{
		Lv = GM->PlayerStats[0].Lv;
		HP = GM->PlayerStats[0].HP;
		MaxHP = GM->PlayerStats[0].MaxHP;
		Atk = GM->PlayerStats[0].Atk;
		Def = GM->PlayerStats[0].Def;
		AtkSpd = GM->PlayerStats[0].AtkSpd;
		XP = GM->PlayerStats[0].XP;
		maxXP = GM->PlayerStats[0].maxXP;
		Tier = GM->PlayerStats[0].Tier;
	}
	else
	{
		GM->PlayerStats[0].Lv = Lv;
		GM->PlayerStats[0].HP = HP;
		GM->PlayerStats[0].MaxHP = MaxHP;
		GM->PlayerStats[0].Atk = Atk;
		GM->PlayerStats[0].Def = Def;
		GM->PlayerStats[0].AtkSpd = AtkSpd;
		GM->PlayerStats[0].XP = XP;
		GM->PlayerStats[0].maxXP = maxXP;
		GM->PlayerStats[0].Tier = Tier;
	}

	UIChange();
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
		Atk += FMath::RandRange(2, 3);
		Def += FMath::RandRange(1, 2);
		break;
	case 2:
		MaxHP += FMath::RandRange(10, 14);
		Atk += FMath::RandRange(4, 7);
		Def += FMath::RandRange(3, 5);
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
		AtkSpd = 1.5;
		Tier = 2;
		classNam = EClassName::Knight;
	}
	if (Lv == 60)
	{
		MaxHP += 10;
		HP = MaxHP;
		Atk += 6;
		Def += 5;
		AtkSpd = 1.f;
		Tier = 3;
		classNam = EClassName::General;
	}

	GM->PlayerStats[0].Lv = Lv;
	GM->PlayerStats[0].HP = HP;
	GM->PlayerStats[0].MaxHP = MaxHP;
	GM->PlayerStats[0].Atk = Atk;
	GM->PlayerStats[0].Def = Def;
	GM->PlayerStats[0].AtkSpd = AtkSpd;
	GM->PlayerStats[0].XP = XP;
	GM->PlayerStats[0].maxXP = maxXP;
	GM->PlayerStats[0].Tier = Tier;

	UIChange();
}

void APlayerBattleTester::GainXP(int32 EXP)
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

void APlayerBattleTester::GetAllStats(int32 &Lvl, int32 &AHp, int32 &AmaxHP, int32 &AAtk, int32 &ADef, int32 &AXP, int32 &AmaxXP, uint8 &jobnum)
{
	Lvl = Lv; AHp = HP; AmaxHP = MaxHP; AAtk = Atk; ADef = Def; AXP = XP; AmaxXP = maxXP; jobnum = 2;
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