// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"

// Sets default values
APlayerBase::APlayerBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerBase::GainXP(int32 EXP)
{
}

void APlayerBase::AtkDamage(int32 Damage)
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
	float nHP = HP, nMHP = MaxHP;
	float CurHP = nHP / nMHP;
	
	DamageHealth(CurHP);
}