// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NPC.h"
#include "NPCRecruiter.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API ANPCRecruiter : public ANPC
{
	GENERATED_BODY()

public:
	ANPCRecruiter();

	//interface functions
	virtual void dialogue();
private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
