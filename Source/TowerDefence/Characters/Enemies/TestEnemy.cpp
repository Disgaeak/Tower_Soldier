// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEnemy.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UMG/Public/Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "../../EnemySpawner.h"
#include "../../TowerDefenceGameMode.h"

ATestEnemy::ATestEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//sets default stats
	Lv = 1;
	HP = 12;
	MaxHP = 12;
	Atk = 3;
	Def = 2;
	AtkSpd = 1.2;
	XP = Lv * Lv + 1;
	GP = MaxHP / 2;
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

void ATestEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->GetAuthGameMode()) { GM = Cast<ATowerDefenceGameMode>(GetWorld()->GetAuthGameMode()); }

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Target"), Targets);
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Spawner"), Spawner);
	if (Spawner[0] != nullptr)
		eSpawn = Cast<AEnemySpawner>(Spawner[0]);
}

void ATestEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestEnemy::GainXP(int32 EXP)
{
	if (EXP > 1)
	{
		Lv = EXP;
		for (int32 i = 1; i <= Lv; i++)
		{
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

			if (i == 30)
			{
				MaxHP += 5;
				HP = MaxHP;
				Atk += 3;
				Def += 3;
				AtkSpd = 1.8;
				Tier = 2;
				classNam = EClassName::Knight;
			}
			if (i == 60)
			{
				MaxHP += 10;
				HP = MaxHP;
				Atk += 6;
				Def += 5;
				AtkSpd = 2.3;
				Tier = 3;
				classNam = EClassName::General;
			}

			HP = MaxHP;
		}
	}
}

void ATestEnemy::AtkDamage(int32 Damage)
{
	int32 minDamage = Damage - (Def * 2);
	if (minDamage > 0)
	{
		if (HP - minDamage > 0)
		{
			HP -= minDamage;
		}
		else
		{
			HP = 0;
			GM->XP += XP;
			GM->Money += GP;
			Destroy();
			eSpawn->CheckEArray();
		}
	}
	float nHP = HP, nMHP = MaxHP;
	float CurHP = nHP / nMHP;

	DamageHealth(CurHP);
}

void ATestEnemy::RangeOverlap(AActor* Other)
{
	if (Other->ActorHasTag(FName("Ally")))
	{
		IBattleInterface* EnemyTarg = Cast<IBattleInterface>(Other);
		int32 curDamage = (Atk + Lv) * 3;
		EnemyTarg->AtkDamage(curDamage);
	}
}