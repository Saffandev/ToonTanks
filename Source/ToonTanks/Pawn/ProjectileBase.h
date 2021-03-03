// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* TrialEffect;

	UPROPERTY(EditDefaultsOnly,Category = "Damage")
	TSubclassOf<UDamageType> Damage;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Audio",meta = (AllowPrivateAccess = "true"))
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere,Category = "CameraShake Effects")
	TSubclassOf<UCameraShake> HitShake;

	UPROPERTY(EditAnyWhere,BlueprintReadOnly,Category = "Properties",meta = (AllowPrivateAccess = "true"))
	float ProjectileSpeed = 1300.f;

	UPROPERTY(EditAnyWhere,BlueprintReadOnly,Category = "Properties",meta = (AllowPrivateAccess = "true"))
	float DamageAmount = 50.f;

	UPROPERTY(EditAnywhere,Category = "Particle Effects")
	UParticleSystem* HitParticleEffect;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,const FVector NormalImpulse,const FHitResult& Hit);

public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
