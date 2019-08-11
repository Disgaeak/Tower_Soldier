// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SubGM.generated.h"

class AEnemySpawner;

UCLASS()
class TOWERDEFENCE_API ASubGM : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASubGM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	UPROPERTY(EditAnywhere, Category = "Spawn", Meta = (BlueprintProtected = true))
	TSubclassOf<AEnemySpawner> ESpawn;
};