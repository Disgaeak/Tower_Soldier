// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Players/PlayerBase.h"
#include "PlayerBattleTester.generated.h"

class IBattleInterface;

UCLASS()
class TOWERDEFENCE_API APlayerBattleTester : public APlayerBase
{
	GENERATED_BODY()

public: 
	APlayerBattleTester();

	//Interface funtions
	virtual void GainXP(int32 EXP);

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
