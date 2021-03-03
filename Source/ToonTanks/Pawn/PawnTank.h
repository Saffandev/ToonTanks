// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnTankBase.h"
#include "PawnTank.generated.h"


class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnTankBase
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Componenets",meta=(AllowPrivateAccess="true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Componenets",meta=(AllowPrivateAccess="true"))
	UCameraComponent* Camera;

	FVector MoveDirection;
	FQuat RotationDirection;
	bool bIsPlayerAlive = true;
	
	APlayerController* PlayerCont;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movements",meta=(AllowPrivateAccess="true"))
	float MoveSpeed = 500.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movements",meta=(AllowPrivateAccess="true"))
	float RotateSpeed = 200.f;

	void CalculateMoveInput(float Axisvalue);
	void CalculateRotateInput(float Axisvalue);

	void Move();
	void Rotate();

public:
	// Sets default values for this pawn's properties
	APawnTank();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void DestructionHandler() override;

	bool GetPlayerLifeStatus();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
