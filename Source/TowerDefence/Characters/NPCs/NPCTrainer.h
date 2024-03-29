// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NPC.h"
#include "NPCTrainer.generated.h"

UCLASS()
class TOWERDEFENCE_API ANPCTrainer : public ANPC
{
	GENERATED_BODY()
	
public:
	ANPCTrainer();

	//interface functions
	virtual void dialogue();

protected:
	
private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
