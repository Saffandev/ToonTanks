// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTorrent.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"


void APawnTorrent::BeginPlay()
{
    Super::BeginPlay();

    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandler,this,&APawnTorrent::CheckFireCondition,FMath::RandRange(FireRate-1,FireRate),true);
}

void APawnTorrent::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    
    
    if(!PlayerTank || DistanceBetween() > FireRange)
    {
        return;   
    }

    RotateTorrent(PlayerTank->GetActorLocation());
    
}


void APawnTorrent::CheckFireCondition()
{
    if(!PlayerTank || !PlayerTank->GetPlayerLifeStatus())
    {
        return ;
    }

    
    if(DistanceBetween() <= FireRange)
    {
        Fire();
    }
    
}

float APawnTorrent::DistanceBetween()
{
    return FVector::Dist(PlayerTank->GetActorLocation(),GetActorLocation());
}

void APawnTorrent::DestructionHandler() 
{
    Super::DestructionHandler();
    Destroy();
    //SetActorHiddenInGame(true);
}
