// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class ABattleCam;
class IBattleInterface;

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

	UFUNCTION()
	void CheckEArray();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle SpawnHandle;
	IBattleInterface* enemSpawn;

	int32 waveCount = 0;//current wave
	int32 spawnCount = 0;
	int32 stageNum;
	TArray<int32> maxWaveCount;
	TArray<int32> numOfEnemytoSpawn; //number of enemies to spawn per wave
	TArray<AActor*> numofEnemies;
	TArray<AActor*> Targets;

	UPROPERTY(EditAnywhere, Category = "Spawn", Meta = (BlueprintProtected = true))
	TSubclassOf<APawn> ToSpawn;

	UPROPERTY(VisibleAnywhere, Category = "BattleCam", Meta = (BlueprintProtected = true))
	ABattleCam* BatCam;
};