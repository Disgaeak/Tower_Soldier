// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Players/BattleInterface.h"
#include "EnemyBase.generated.h"

class AEnemySpawner;

UCLASS()
class TOWERDEFENCE_API AEnemyBase : public ACharacter, public IBattleInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

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
	int32 GP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Stats")
	EClassName classNam;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Stats")
	int32 Tier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Stats")
	EJobName jobNam;

	AEnemySpawner* eSpawn;
	FTimerHandle EAtkHandle;

	//set attack animation enemy is in range
	UPROPERTY(BlueprintReadWrite, category = "Anim")
	bool bCanAttack;

	//sets health(percent) in blueprint
	UFUNCTION(BlueprintImplementableEvent)
	void DamageHealth(const float &Dmg);

	//sets level and stats for UI widget
	UFUNCTION(BlueprintImplementableEvent)
	void SetUILV();

	//Interface funtions
	virtual void GainXP(int32 EXP);
	virtual void AtkDamage(int32 Damage);

	UFUNCTION(BlueprintCallable)
	void GetAllStats(int32 &Lvl, int32 &AHp, int32 &AmaxHP, int32 &AAtk, int32 &ADef, int32 &AXP, int32 &AmaxXP, uint8 &jobnum);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//creates an inherited Widget of HP bar
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* HealthBar;

	//creates box collider for battle detection
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Box", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Atkrange;

	FORCEINLINE class UWidgetComponent* GetHPBar() const { return HealthBar; }
	FORCEINLINE class UBoxComponent* GetAtkBox() const { return Atkrange; }
};