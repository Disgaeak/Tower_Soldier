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

USTRUCT(BlueprintType)
struct FEnemyinfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "stats")
	int32 Lv = 0;

	UPROPERTY(BlueprintReadWrite, Category = "stats")
	uint8 job = 0;

	UPROPERTY(BlueprintReadWrite, Category = "stats")
	int32 curstage = 0;
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

	//when enemy reaches goal
	UFUNCTION(BlueprintCallable)
	void AttackTown(int32 damage, uint8 job);

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int32 XP;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int32 Money;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	int32 townMaxHP;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	int32 TownHP;

	UPROPERTY(BlueprintReadOnly, Category = "Deploy")
	int32 MiaNum;

	UPROPERTY(BlueprintReadOnly, Category = "Deploy")
	int32 TownGuardNum;

	//keeps track of all units stats to save game
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	TArray<FGMStats> PlayerStats;

	UPROPERTY(BlueprintReadWrite, Category = "Enemy")
	TArray<FEnemyinfo> EscapeEnemy;

protected:
	virtual void BeginPlay() override;

private:
	int32 StageNum;
};