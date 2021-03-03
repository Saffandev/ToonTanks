// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class APawnTank;
class APawnTorrent;
class ATankPlayerControllerBase;

UCLASS()
class TOONTANKS_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	APawnTank* PlayerTank;
	int32 TorrentNumber = 0;
	ATankPlayerControllerBase* PlayerControllerRef;
	

	void HandleGameStart();	
	void HandleGameEnd(bool PlayerWon);	

public:

	void ActorDied(AActor* DeadActor);	

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "GameLoop")
	int32 StartCountDown = 0;
	virtual void BeginPlay() override;	
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameEnd(bool PlayerWon);

	
};
