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

	void SpawnWave();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int32 waveCount;
	int32 maxWaveCount;

	UPROPERTY(EditAnywhere, Category = "Spawn", Meta = (BlueprintProtected = true))
	TSubclassOf<APawn> ToSpawn;
};