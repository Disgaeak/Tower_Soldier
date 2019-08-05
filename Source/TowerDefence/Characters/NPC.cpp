// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FText ANPC::dialogue()
{
	FText basic = FText::FromString("where'ya headed?");
	return basic;
}

Alliance ANPC::GetAlly()
{
	return jobName;
}