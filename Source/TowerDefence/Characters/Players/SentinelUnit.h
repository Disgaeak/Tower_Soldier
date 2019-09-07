// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Players/PlayerBase.h"
#include "SentinelUnit.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API ASentinelUnit : public APlayerBase
{
	GENERATED_BODY()

public:
	ASentinelUnit();

	//Interface funtions
	virtual void GainXP(int32 EXP);
	virtual void GetAllStats(int32 &Lvl, int32 &AHp, int32 &AmaxHP, int32 &AAtk, int32 &ADef, int32 &AXP, int32 &AmaxXP, uint8 &jobnum);

	//AtkRange Overlap function
	UFUNCTION(BlueprintCallable)
	void RangeOverlap(AActor* Other);

	UFUNCTION(BlueprintCallable)
	void EndAtkTime();

private:
	IBattleInterface* EnemyTarg;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void LevelUp();
	void StartAtkDmg();
};