// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "PawnTankBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;

UCLASS()
class TOONTANKS_API APawnTankBase : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TorrentMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawn;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileBaseClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere,Category = "Particle Effects")
	UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere,Category = "CameraShake Effects")
	TSubclassOf<UCameraShake> DeathShake;


public:
	// Sets default values for this pawn's properties
	APawnTankBase();
	virtual void DestructionHandler();


protected:
	void RotateTorrent(FVector LookAtTarget);

	void Fire();

	
	

};
