// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCTrainer.h"
#include "../../WidgetControl.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"

ANPCTrainer::ANPCTrainer()
{
	Tags.Add(FName("Trainer"));
}

void ANPCTrainer::BeginPlay()
{
	Super::BeginPlay();
}

void ANPCTrainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPCTrainer::dialogue()
{
	if (widCon != nullptr)
	{
		widCon->AddToViewport();
	}
}