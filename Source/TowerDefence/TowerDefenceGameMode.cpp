// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TowerDefenceGameMode.h"
#include "TowerDefenceCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "EnemySpawner.h"

ATowerDefenceGameMode::ATowerDefenceGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Mannequin/Character/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// 0 = Mia, 1 = Soldier Unit, 2 = Klaine, 3 = Sentinel Unit
	PlayerStats.SetNum(4);
	townMaxHP = 10;
	TownHP = 10;
	MiaNum = 1;
	KlaineNum = 1;
	TownGuardNum = 3;
	SentinelNum = 0;

	//0 = tutorial: klaine saves player. 1 = unlock 1st extra map
	Events.SetNum(5);
	//0 = Sentinel, 1 = Healer, 2 = Rider, 3 = Archer
	Recruited.SetNum(4);
}

void ATowerDefenceGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ATowerDefenceGameMode::SetStage(int32 stageCode)
{
	StageNum = stageCode;
}

int32 ATowerDefenceGameMode::GetStage()
{
	return StageNum;
}

void ATowerDefenceGameMode::AttackTown(int32 damage, uint8 job)
{
	if (StageNum == 0)
	{
		TownHP -= damage;
	}
	else
	{
		FEnemyinfo holder;
		holder.curstage = StageNum;
		holder.Lv = damage;
		holder.job = job;

		EscapeEnemy.Add(holder);
	}
}

void ATowerDefenceGameMode::ProgressStory()
{
	MiaNum = 1;
	KlaineNum = 1;

	if (StageNum >= Story)
	{
		if(StageNum == 2){}
		else
		{
			Story++;
		}
	}
}
