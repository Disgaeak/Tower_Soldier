// Fill out your copyright notice in the Description page of Project Settings.


#include "SubGM.h"
#include "EnemySpawner.h"

// Sets default values
ASubGM::ASubGM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASubGM::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASubGM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}