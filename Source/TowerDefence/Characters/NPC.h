// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCInterface.h"
#include "NPC.generated.h"

class UWidgetControl;

UCLASS()
class TOWERDEFENCE_API ANPC : public ACharacter, public INPCInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

	//interface functions
	virtual void dialogue();

	//closes current widget
	UFUNCTION(BlueprintCallable)
	void closeWidget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "UI", Meta = (BlueprintProtected = true))
	UWidgetControl* widCon;
};