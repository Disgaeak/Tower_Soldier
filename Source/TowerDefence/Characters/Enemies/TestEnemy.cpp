// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEnemy.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ATestEnemy::ATestEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HP = 5;
	Atk = 3;
	Def = 1;
	AtkSpd = 1.2;
}

void ATestEnemy::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Target"), Targets);
}

void ATestEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}