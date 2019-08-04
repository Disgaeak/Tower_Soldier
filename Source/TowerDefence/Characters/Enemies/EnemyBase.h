// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class TOWERDEFENCE_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

	//basic stats
	UPROPERTY(BlueprintReadOnly, category = "Stats")
	int32 HP;
	UPROPERTY(BlueprintReadOnly, category = "Stats")
	int32 Atk; 
	UPROPERTY(BlueprintReadOnly, category = "Stats")
	int32 Def;
	UPROPERTY(BlueprintReadOnly, category = "Stats")
	float AtkSpd;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};