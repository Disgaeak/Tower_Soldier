// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/EnemyBase.h"
#include "TestEnemy.generated.h"


UCLASS()
class TOWERDEFENCE_API ATestEnemy : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestEnemy();

	//Interface funtions
	virtual void GainXP(int32 EXP);

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
};