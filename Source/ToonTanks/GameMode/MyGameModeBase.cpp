// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "ToonTanks/Pawn/PawnTank.h"
#include "ToonTanks/Pawn/PawnTorrent.h"
#include "ToonTanks/PlayerController/TankPlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"


void AMyGameModeBase::BeginPlay() 
{
    Super::BeginPlay();
    
    //Get reference and game win/lose conditoin
    //call handlegamestart() to initialise start countdown,torrent activation and pawn check etc.

    TArray<AActor*> TorrentActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(),APawnTorrent::StaticClass(),TorrentActors);

    TorrentNumber = TorrentActors.Num();
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));
    PlayerControllerRef = Cast<ATankPlayerControllerBase>(UGameplayStatics::GetPlayerController(this,0));

    HandleGameStart();
}


void AMyGameModeBase::HandleGameStart() 
{
    //implement startcountdown, torrent activation and player pawn etc.
    //call the blueprint version of the gamestart;
    GameStart();
    if(PlayerControllerRef)
        {
            UE_LOG(LogTemp,Warning,TEXT("Entered player controller"));
            PlayerControllerRef->SetPlayerEnableState(false);
            FTimerHandle PlayerEnableHanle;
            FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,&ATankPlayerControllerBase::SetPlayerEnableState,true);
            GetWorld()->GetTimerManager().SetTimer(PlayerEnableHanle,PlayerEnableDelegate,StartCountDown,false);
        }
}

void AMyGameModeBase::HandleGameEnd(bool PlayerWon) 
{
    //Check who diese
    //if all torrent died then won screen
    //else if the player died then lose screen
    //call blueprint version 

    GameEnd(PlayerWon);
}

void AMyGameModeBase::ActorDied(AActor* DeadActor) 
{
    //who dies player or torrent
    UE_LOG(LogTemp,Warning,TEXT("Dead"));

    if(DeadActor == PlayerTank)
    {
        PlayerTank->DestructionHandler();    
        HandleGameEnd(false);

        if(PlayerControllerRef)
        {
           
            PlayerControllerRef->SetPlayerEnableState(false);
           
        }
        

    }

    else if(APawnTorrent* DestroyedTorrent = Cast<APawnTorrent>(DeadActor))
    {
        DestroyedTorrent->DestructionHandler();
        if(--TorrentNumber <= 0)
        {
            HandleGameEnd(true);
        }
    }
}


