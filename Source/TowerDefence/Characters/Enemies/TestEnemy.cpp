// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEnemy.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UMG/Public/Components/WidgetComponent.h"

ATestEnemy::ATestEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//sets default stats
	Lv = 1;
	HP = 5;
	MaxHP = 5;
	Atk = 3;
	Def = 1;
	AtkSpd = 1.2;
	XP = 2;
	GP = 2;

	//create HP widget
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI health"));
	HealthBar->SetupAttachment(RootComponent);
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBar->SetDrawSize(FVector2D(200.f, 60.f));
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