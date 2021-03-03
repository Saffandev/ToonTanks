// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:

	void SetPlayerEnableState(bool PlayerEnableState);
	
};
