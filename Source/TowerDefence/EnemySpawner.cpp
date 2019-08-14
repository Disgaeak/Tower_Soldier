// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "Engine/Classes/GameFramework/Character.h"
#include "Characters/BattleCam.h"
#include "Kismet/GameplayStatics.h"

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

	Tags.Add(FName("Spawner"));
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Camera"), Targets);
	if (Targets[0] != nullptr)
		BatCam = Cast<ABattleCam>(Targets[0]);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEnemySpawner::SpawnWave(int32 stageCode)
{
	stageNum = stageCode;
	if (BatCam != nullptr)
		BatCam->bNextWave = false;

	waveCount++;
	GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &AEnemySpawner::EnemyTime, 3.f, true, 0.5f);
}

void AEnemySpawner::EnemyTime()
{
	//spawn Enemies from this point
	if (ToSpawn != nullptr)
	{
		//checks which wave
		if (waveCount <= maxWaveCount[0])
		{
			//checks how many have spawned
			if (spawnCount < numOfEnemytoSpawn[stageNum] + waveCount && ToSpawn != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Yay"))
				APawn* spawnd = GetWorld()->SpawnActor<APawn>(ToSpawn);
				spawnd->SetActorLocation(GetActorLocation());
				spawnd->SpawnDefaultController();
				spawnd->Tags.Add(FName("Enemy"));

				numofEnemies.Add(spawnd);
				spawnCount++;
			}
			else
			{
				GetWorld()->GetTimerManager().ClearTimer(SpawnHandle);
				spawnCount = 0;
				if (BatCam != nullptr && waveCount < maxWaveCount[0])
					BatCam->bNextWave = true;
			}
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(SpawnHandle);
		}
	}
}

void AEnemySpawner::CheckEArray()
{
	for(int i = 1; i <= numofEnemies.Num(); ++i)
	{
		if (numofEnemies[i] == nullptr)
			numofEnemies.RemoveAt(i);

		i--;
	}
}