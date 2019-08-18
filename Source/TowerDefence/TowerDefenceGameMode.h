// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenceGameMode.generated.h"

class AEnemySpawner;

USTRUCT(BlueprintType)
struct FGMStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "stats")
	int32 Lv = 0;
	UPROPERTY(BlueprintReadWrite, Category = "stats")
	int32 HP = 0;
	UPROPERTY(BlueprintReadWrite, Category = "stats")
	int32 MaxHP = 0;
	UPROPERTY(BlueprintReadWrite, Category = "stats")
	int32 Atk = 0;
	UPROPERTY(BlueprintReadWrite, Category = "stats")
	int32 Def = 0;
	UPROPERTY(BlueprintReadWrite, Category = "stats")
	float AtkSpd = 0;
	UPROPERTY(BlueprintReadWrite, Category = "stats")
	int32 XP = 0;
	UPROPERTY(BlueprintReadWrite, Category = "stats")
	int32 maxXP = 0;
	UPROPERTY(BlueprintReadWrite, Category = "stats")
	int32 Tier = 0;
};

UCLASS(minimalapi)
class ATowerDefenceGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATowerDefenceGameMode();

	UFUNCTION(BlueprintCallable)
	void SetStage(int32 stageCode);

	UFUNCTION(BlueprintCallable)
	int32 GetStage();

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int32 XP;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int32 Money;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	TArray<FGMStats> PlayerStats;

protected:
	virtual void BeginPlay() override;

private:
	int32 StageNum;
};