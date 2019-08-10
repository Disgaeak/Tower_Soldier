// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BattleCam.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);// Called for forwards/backward input
	void MoveRight(float Value);// Called for side to side input
	FHitResult RayLine();

	FVector Start;
	FVector End;
};