// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEnemy.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UMG/Public/Components/WidgetComponent.h"
#include "Components/BoxComponent.h"

ATestEnemy::ATestEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//sets default stats
	Lv = 1;
	HP = 12;
	MaxHP = 12;
	Atk = 3;
	Def = 2;
	AtkSpd = 1.2;
	XP = 4;
	GP = 4;

	//create HP widget
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI health"));
	HealthBar->SetupAttachment(RootComponent);
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBar->SetDrawSize(FVector2D(200.f, 60.f));

	//create box collider
	Atkrange = CreateDefaultSubobject<UBoxComponent>(TEXT("Range"));
	Atkrange->SetupAttachment(RootComponent);
	Atkrange->SetBoxExtent(FVector(70.f, 32.f, 32.f));
}

void ATestEnemy::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Target"), Targets);
}

void ATestEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestEnemy::GainXP(int32 EXP)
{
}

void ATestEnemy::RangeOverlap(AActor* Other)
{
	if (Other->ActorHasTag(FName("Ally")))
	{
		IBattleInterface* EnemyTarg = Cast<IBattleInterface>(Other);
		int32 curDamage = (Atk + Lv) * 3;
		EnemyTarg->AtkDamage(curDamage);
	}
}