// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "../../EnemySpawner.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::GainXP(int32 EXP)
{
}

void AEnemyBase::AtkDamage(int32 Damage)
{
	
}

void AEnemyBase::GetAllStats(int32 & Lvl, int32 & AHp, int32 & AmaxHP, int32 & AAtk, int32 & ADef, int32 & AXP, int32 & AmaxXP, uint8 &jobnum)
{
	Lvl = Lv; AHp = HP; AmaxHP = MaxHP; AAtk = Atk; ADef = Def; AXP = XP; jobnum = (uint8)jobNam;
}
