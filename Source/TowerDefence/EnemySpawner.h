// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class TOWERDEFENCE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UFUNCTION(BlueprintCallable)
	void SpawnWave(int32 stageCode);

	UFUNCTION()
	void EnemyTime();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle SpawnHandle;

	int32 waveCount;//current wave
	int32 spawnCount = 0;
	int32 stageNum;
	TArray<int32> maxWaveCount;
	TArray<int32> numOfEnemytoSpawn; //number of enemies to spawn per wave

	UPROPERTY(EditAnywhere, Category = "Spawn", Meta = (BlueprintProtected = true))
	TSubclassOf<APawn> ToSpawn;
};