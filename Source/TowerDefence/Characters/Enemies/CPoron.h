// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/EnemyBase.h"
#include "CPoron.generated.h"

class ATowerDefenceGameMode;

UCLASS()
class TOWERDEFENCE_API ACPoron : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	ACPoron();

	//Interface funtions
	virtual void GainXP(int32 EXP);
	virtual void AtkDamage(int32 Damage);

	//AtkRange Overlap function
	UFUNCTION(BlueprintCallable)
	void RangeOverlap(AActor* Other);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<AActor*> Targets;
	TArray<AActor*> Spawner;

	ATowerDefenceGameMode* GM;

};
