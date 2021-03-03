// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFrameWork/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;
	ProjectileMesh->OnComponentHit.AddDynamic(this,&AProjectileBase::OnHit);

	TrialEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trial Effect"));
	TrialEffect->SetupAttachment(ProjectileMesh);
	

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1300.f;
	ProjectileMovement->MaxSpeed = 1300.f;
	InitialLifeSpan = 3.0f;

}	

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	

}


void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,const FVector NormalImpulse,const FHitResult& Hit) 
{
	AActor* MyOwner = GetOwner();

	UGameplayStatics::SpawnEmitterAtLocation(this,HitParticleEffect,GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(this,HitSound,GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);

	if(!MyOwner)
	{
		UE_LOG(LogTemp,Warning,TEXT("hit"));
		return;
	}

	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor,DamageAmount,MyOwner->GetInstigatorController(),this,Damage);
		
		UE_LOG(LogTemp,Warning,TEXT("Damaged"));
	}
	
	Destroy();
	
}
