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

	PlayerStats.SetNum(2);
	townMaxHP = 10;
	TownHP = 10;
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
}
