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

//determines the role in battle and stat growth
UENUM()
enum class EClassName : uint8
{
	NONE,
	//Types that move during battle
	Soldier,
	Knight,
	General,
	//Types that do not move(Ally only) or Move & attack(Enemy only)
	Guard,
	Sentinel,
	Guardian,
	//Types that ignore and go for goal
	Thief,
	Rogue,
	Assassin,
	//Types that move but remain distant
	Archer,
	Grand_Bowman,
	Sagittarius,
	//Enemy only: ignores goal and go after Allies
	Berserker,
	Hellion,
	Genocider,
	//Ally only: cannot attack, only heals
	Cleric,
	Maiden,
	Angel,
	//Wyvern or dragon unit: only attacks in straight line and returns to spawned position as guard
	Enuclea,
	Murum,
	Dahakha
};

//the type of enemy or player
UENUM()
enum class EJobName : uint8
{
	NONE,
	leaflet, //Poron jobs
	Hero
};

class TOWERDEFENCE_API IBattleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//used for Allies to gain XP, but Enemies to indicate Level
	virtual void GainXP(int32 EXP) = 0;

	virtual void AtkDamage(int32 Damage) = 0;
	virtual void GetAllStats(int32 &Lvl, int32 &AHp, int32 &AmaxHP, int32 &AAtk, int32 &ADef, int32 &AXP, int32 &AmaxXP) = 0;
};
