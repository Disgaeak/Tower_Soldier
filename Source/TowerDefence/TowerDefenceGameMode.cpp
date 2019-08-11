// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TowerDefenceGameMode.h"
#include "TowerDefenceCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATowerDefenceGameMode::ATowerDefenceGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Mannequin/Character/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void ATowerDefenceGameMode::SetStage(int32 stageCode)
{
	StageNum = stageCode;
}

void ATowerDefenceGameMode::BeginPlay()
{
}
