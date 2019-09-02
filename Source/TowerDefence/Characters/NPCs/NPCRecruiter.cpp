// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCRecruiter.h"
#include "../../WidgetControl.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"

ANPCRecruiter::ANPCRecruiter()
{
	Tags.Add(FName("Recruiter"));
}

void ANPCRecruiter::BeginPlay()
{
	Super::BeginPlay();
}

void ANPCRecruiter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPCRecruiter::dialogue()
{
	if (widCon != nullptr)
	{
		widCon->AddToViewport();
	}
}