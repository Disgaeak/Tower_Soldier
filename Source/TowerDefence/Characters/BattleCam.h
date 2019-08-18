// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BattleCam.generated.h"

class UWidgetControl;
class ATowerDefenceGameMode;
class ATowerDefenceCharacter;
class IBattleInterface;

UCLASS()
class TOWERDEFENCE_API ABattleCam : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABattleCam();

	//camera
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Cam;

	UFUNCTION(BlueprintCallable)
	void SelectedPawn(int32 charaNum);

	void OpenMenu();

	void endBattleSwitch();

	UPROPERTY(BlueprintReadOnly, category = "Spawn")
	bool bNextWave = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Point();

	void Cancel();

private:
	void MoveForward(float Value);// Called for forwards/backward input
	void MoveRight(float Value);// Called for side to side input
	FHitResult RayLine();

	FVector Start;
	FVector End;
	FVector LOC;

	TSubclassOf<APawn> SelSoldier;
	ATowerDefenceGameMode* GM;
	TArray<AActor*> numofPlayers;
	IBattleInterface* AllyRef;

	UPROPERTY(EditAnywhere, Category = "Ally", Meta = (BlueprintProtected = true))
	TSubclassOf<APawn> ToSpawn;

	UPROPERTY(EditAnywhere, Category = "BattleCam", Meta = (BlueprintProtected = true))
	APawn* hubChara;

	UPROPERTY(EditAnywhere, Category = "UI", Meta = (BlueprintProtected = true))
	UWidgetControl* widCon;
};