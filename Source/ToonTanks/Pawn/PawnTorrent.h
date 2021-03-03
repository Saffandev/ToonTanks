// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnTankBase.h"
#include "GameFramework/Actor.h"
#include "PawnTorrent.generated.h"

class APawnTank;
UCLASS()
class TOONTANKS_API APawnTorrent : public APawnTankBase
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	virtual void DestructionHandler() override;

private:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Combat",meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.f;

	APawnTank* PlayerTank;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Combat",meta = (AllowPrivateAccess = "true"))
	float FireRange;

	void CheckFireCondition();
	float DistanceBetween();

	FTimerHandle FireRateTimerHandler;
	

protected:

	virtual void BeginPlay() override;

	
};
