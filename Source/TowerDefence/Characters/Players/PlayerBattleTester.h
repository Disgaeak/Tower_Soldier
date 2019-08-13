// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Players/PlayerBase.h"
#include "PlayerBattleTester.generated.h"

UCLASS()
class TOWERDEFENCE_API APlayerBattleTester : public APlayerBase
{
	GENERATED_BODY()

	//creates an inherited Widget of HP bar
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* HealthBar;

public: 
	APlayerBattleTester();

	//Interface funtions
	virtual void GainXP(int32 EXP);
	virtual void AtkDamage(int32 Damage);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void LevelUp();

	FORCEINLINE class UWidgetComponent* GetHPBar() const { return HealthBar; }
};
