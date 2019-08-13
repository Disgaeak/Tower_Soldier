// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

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
	int32 minDamage = Damage - (Def * 2);
	if (minDamage > 0)
	{
		if (HP - minDamage > 0)
		{
			HP -= minDamage;
		}
		else
		{
			HP = 0;
		}
	}

	float CurHP = HP / MaxHP;
	DamageHealth(CurHP);
}