// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "Engine/Classes/GameFramework/Character.h"
#include "Characters/BattleCam.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Players/BattleInterface.h"
#include "TowerDefenceGameMode.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	maxWaveCount.SetNum(3); maxWaveCount[0] = 2; maxWaveCount[1] = 3; maxWaveCount[2] = 5;
	numOfEnemytoSpawn.SetNum(3); numOfEnemytoSpawn[0] = 1; numOfEnemytoSpawn[1] = 2; numOfEnemytoSpawn[2] = 4;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("Spawner"));
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Camera"), Targets);
	if (Targets[0] != nullptr)
		BatCam = Cast<ABattleCam>(Targets[0]);

	if (GetWorld()->GetAuthGameMode()) { GM = Cast<ATowerDefenceGameMode>(GetWorld()->GetAuthGameMode()); }
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

	if (bCanSPawnExtra)
	{
		GetWorld()->GetTimerManager().SetTimer(XtraSpawn, this, &AEnemySpawner::NowSpawnXtra, 2.f, true, 0.5f);
	}
	else
	{
		waveCount++;
		GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &AEnemySpawner::EnemyTime, 3.f, true, 0.5f);
	}
}

void AEnemySpawner::EnemyTime()
{
	//spawn Enemies from this point
	if (ToSpawn != nullptr)
	{
		//checks which wave
		if (waveCount <= maxWaveCount[stageNum])
		{
			//checks how many have spawned
			if (spawnCount < numOfEnemytoSpawn[stageNum] + waveCount)
			{
				APawn* spawnd = GetWorld()->SpawnActor<APawn>(ToSpawn);
				spawnd->SetActorLocation(GetActorLocation());
				spawnd->SpawnDefaultController();
				spawnd->Tags.Add(FName("Enemy"));

				//levels up if needed
				enemSpawn = Cast<IBattleInterface>(spawnd);
				enemSpawn->GainXP(waveCount);

				spawnCount++;
			}
			else
			{
				GetWorld()->GetTimerManager().ClearTimer(SpawnHandle);
				if (BatCam != nullptr && waveCount < maxWaveCount[stageNum])
				{
					BatCam->bNextWave = true;
					spawnCount = 0;
				}
			}
		}
	}
}

void AEnemySpawner::CheckEArray()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Enemy"), numofEnemies);

	//check if the battle is finish to return to town
	if (numofEnemies.Num() == 0)
	{
		if (spawnCount == numOfEnemytoSpawn[stageNum] + waveCount)
		{
			if (waveCount == maxWaveCount[stageNum])
			{
				SpawnExtra();
				if (bHasExtraEnemy == false)
				{
					waveCount = 0;
					spawnCount = 0;
					BatCam->bNextWave = true;
					BatCam->endBattleSwitch();
				}
				else
				{
					bCanSPawnExtra = true;
					BatCam->bNextWave = true;
				}
			}
		}
	}
}

void AEnemySpawner::SpawnExtra()
{
	//checks if there is any enemy from the previous stage
	if (GM->EscapeEnemy.Num() > 0)
	{
		for (int i = 0; i < GM->EscapeEnemy.Num(); i++)
		{
			if (GM->EscapeEnemy[i].curstage > GM->GetStage())
			{
				bHasExtraEnemy = true;
				break;
			}
			else
			{
				bHasExtraEnemy = false;
				GetWorld()->GetTimerManager().ClearTimer(XtraSpawn);
			}
		}
	}
	else
	{
		bHasExtraEnemy = false;
	}
}

void AEnemySpawner::NowSpawnXtra()
{
	//spawn Enemies from this point
	if (ToSpawn != nullptr)
	{
		for (int i = 0; i < GM->EscapeEnemy.Num(); i++)
		{
			if (GM->EscapeEnemy[i].curstage > GM->GetStage())
			{
				APawn* spawnd = GetWorld()->SpawnActor<APawn>(ToSpawn);
				spawnd->SetActorLocation(GetActorLocation());
				spawnd->SpawnDefaultController();
				spawnd->Tags.Add(FName("Enemy"));

				//levels up if needed
				enemSpawn = Cast<IBattleInterface>(spawnd);
				enemSpawn->GainXP(GM->EscapeEnemy[i].Lv);
				GM->EscapeEnemy.RemoveAt(i);
				break;
			}
		}
	}
}