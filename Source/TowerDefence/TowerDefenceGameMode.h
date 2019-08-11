// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenceGameMode.generated.h"

class AEnemySpawner;

UCLASS(minimalapi)
class ATowerDefenceGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATowerDefenceGameMode();

	UFUNCTION(BlueprintCallable)
	void SetStage(int32 stageCode);

protected:
	virtual void BeginPlay() override;

private:
	int32 StageNum;
};