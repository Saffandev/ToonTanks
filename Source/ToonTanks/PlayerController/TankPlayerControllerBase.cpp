// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerControllerBase.h"



void ATankPlayerControllerBase::SetPlayerEnableState(bool PlayerEnableState) 
{
    if(PlayerEnableState)
    {
        GetPawn()->EnableInput(this);
        UE_LOG(LogTemp,Warning,TEXT("Disable Input"));
        
    }   

    else
    {
        UE_LOG(LogTemp,Warning,TEXT("Disable Input"));
        GetPawn()->DisableInput(this);
    }

    bShowMouseCursor = PlayerEnableState;
}
