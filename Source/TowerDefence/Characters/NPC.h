// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCInterface.h"
#include "NPC.generated.h"

UCLASS()
class TOWERDEFENCE_API ANPC : public ACharacter, public INPCInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

	//interface functions
	virtual FText dialogue();
	virtual Alliance GetAlly();

	UPROPERTY(EditAnywhere, category = "Job")
	Alliance jobName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
