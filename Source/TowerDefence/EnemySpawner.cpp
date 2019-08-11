// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "Engine/Classes/GameFramework/Character.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	maxWaveCount.SetNum(1); maxWaveCount[0] = 2;
	numOfEnemytoSpawn.SetNum(1); numOfEnemytoSpawn[0] = 2;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnWave(int32 stageCode)
{
	stageNum = stageCode;
	GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &AEnemySpawner::EnemyTime, 5.f, true);
}

void AEnemySpawner::EnemyTime()
{
	//spawn Enemies from this point
	if (ToSpawn != nullptr)
	{
		if (spawnCount < numOfEnemytoSpawn[stageNum])
		{
			APawn* spawnd = GetWorld()->SpawnActor<APawn>(ToSpawn);
			spawnd->SetActorLocation(GetActorLocation());
			spawnd->SpawnDefaultController();
			spawnd->Tags.Add(FName("Enemy"));

			spawnCount++;
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(SpawnHandle);
		}
	}
}