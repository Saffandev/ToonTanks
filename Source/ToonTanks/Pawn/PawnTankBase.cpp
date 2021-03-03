// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTankBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectileBase.h"

// Sets default values
APawnTankBase::APawnTankBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	 BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	 BaseMesh->SetupAttachment(RootComponent);

	 TorrentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Torrent Mesh"));
	 TorrentMesh->SetupAttachment(BaseMesh);

	 ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	 ProjectileSpawn->SetupAttachment(TorrentMesh);

	
	  

}

void APawnTankBase::RotateTorrent(FVector LookAtTarget) 
{
	FVector CleanLookAtTarget = FVector(LookAtTarget.X,LookAtTarget.Y,TorrentMesh->GetComponentLocation().Z);
	FVector StartLocation = TorrentMesh->GetComponentLocation();
	FRotator LookAtRotation = FVector(CleanLookAtTarget - StartLocation).Rotation();
	TorrentMesh->SetWorldRotation(LookAtRotation);
}

void APawnTankBase::Fire() 
{
	UE_LOG(LogTemp, Warning, TEXT("Fire in the hole"));
	if(ProjectileBaseClass)
	{
		
		UGameplayStatics::SpawnSoundAtLocation(this,FireSound,GetActorLocation());
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileBaseClass,ProjectileSpawn->GetComponentLocation(),ProjectileSpawn->GetComponentRotation());
		Projectile->SetOwner(this);
	}
}

void APawnTankBase::DestructionHandler() 
{
	UGameplayStatics::SpawnEmitterAtLocation(this,DeathParticle,GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(this,DeathSound,GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);
}


