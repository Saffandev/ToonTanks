// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"


APawnTank::APawnTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
    
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
    PlayerCont = Cast<APlayerController>(GetController());

}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    Move();
    Rotate();   
    if(PlayerCont)
    {
        FHitResult HitResult;
        PlayerCont->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
        RotateTorrent(HitResult.ImpactPoint);
    }
    
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if(GetPlayerLifeStatus())
    {
        PlayerInputComponent->BindAxis("MoveForward",this,&APawnTank::CalculateMoveInput);
        PlayerInputComponent->BindAxis("Turn",this,&APawnTank::CalculateRotateInput);
        PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
    }

}


void APawnTank::CalculateMoveInput(float Axisvalue) 
{
    MoveDirection = FVector(MoveSpeed * Axisvalue * GetWorld()->DeltaTimeSeconds,0,0);
}

void APawnTank::CalculateRotateInput(float Axisvalue) 
{
   
    float Rotate = RotateSpeed * Axisvalue * GetWorld()->DeltaTimeSeconds;
    FRotator Rotation= FRotator(0,Rotate,0);
    RotationDirection = FQuat(Rotation);
    
}

void APawnTank::Move() 
{
    AddActorLocalOffset(MoveDirection,true);
}

void APawnTank::Rotate() 
{
    AddActorLocalRotation(RotationDirection,true);
}

void APawnTank::DestructionHandler() 
{
    Super::DestructionHandler(); 
    bIsPlayerAlive = false;
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);

}

bool APawnTank::GetPlayerLifeStatus()
{
    return bIsPlayerAlive;
}