// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BattleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBattleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOWERDEFENCE_API IBattleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//used for Allies to gain XP, but Enemies to indicate Level
	virtual void GainXP(int32 EXP) = 0;

	virtual void AtkDamage(int32 Damage) = 0;
};