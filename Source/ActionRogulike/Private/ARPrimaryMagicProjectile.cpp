// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPrimaryMagicProjectile.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <Kismet/GameplayStatics.h>

AARPrimaryMagicProjectile::AARPrimaryMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AARPrimaryMagicProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), destroy_particle, Hit.ImpactPoint, FRotator::ZeroRotator, FVector::OneVector, true, EPSCPoolMethod::AutoRelease);
	GetWorld()->DestroyActor(this);
}

void AARPrimaryMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	sphere_comp->OnComponentHit.AddDynamic(this, &AARPrimaryMagicProjectile::OnHit);
}
