// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BattleInterface.h"
#include "PlayerBase.generated.h"

class ATowerDefenceGameMode;

UCLASS()
class TOWERDEFENCE_API APlayerBase : public ACharacter, public IBattleInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerBase();

	//basic stats
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Stats")
	int32 Lv;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Stats")
	int32 HP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Stats")
	int32 MaxHP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Stats")
	int32 Atk;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Stats")
	int32 Def;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Stats")
	float AtkSpd;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Stats")
	int32 XP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Stats")
	int32 maxXP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Stats")
	int32 Tier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Stats")
	EClassName classNam;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Stats")
	EJobName jobNam;
	UPROPERTY(BlueprintReadWrite, category = "Stats")
	bool HasFound; //used for find any enemies in atk range

	FTimerHandle AtkHandle;
	ATowerDefenceGameMode* GM;

	//set attack animation enemy is in range
	UPROPERTY(BlueprintReadWrite, category = "Anim")
	bool bCanAttack;

	//sets health(percent) in blueprint
	UFUNCTION(BlueprintImplementableEvent)
	void DamageHealth(const float &Dmg);

	//updates UI
	UFUNCTION(BlueprintImplementableEvent)
	void UIChange();

	//Interface funtions
	UFUNCTION(BlueprintCallable)
	virtual void GainXP(int32 EXP);

	void AtkDamage(int32 Damage);

	UFUNCTION(BlueprintCallable)
	virtual void GetAllStats(int32 &Lvl, int32 &AHp, int32 &AmaxHP, int32 &AAtk, int32 &ADef, int32 &AXP, int32 &AmaxXP, uint8 &jobnum);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//creates an inherited Widget of HP bar
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* HealthBar;

	//creates box collider for battle detection
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Box", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Atkrange;

	FORCEINLINE class UWidgetComponent* GetHPBar() const { return HealthBar; }
	FORCEINLINE class UBoxComponent* GetAtkBox() const { return Atkrange; }
};