// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPrimaryMagicProjectile.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <Kismet/GameplayStatics.h>
#include "AttributeComponent.h"

AARPrimaryMagicProjectile::AARPrimaryMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AARPrimaryMagicProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* instigator = Cast<AActor>(GetInstigator());
	if (instigator == OtherActor) return;
	if (OtherActor) {
		UAttributeComponent* attrib_comp = Cast<UAttributeComponent>(OtherActor->GetComponentByClass(UAttributeComponent::StaticClass()));
		if (attrib_comp) {
			attrib_comp->ApplyHealthDelta(instigator, -20.0f);
		}
	}
	if (ensure(ParticleOnDestroy)) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleOnDestroy, SweepResult.ImpactPoint, FRotator::ZeroRotator, FVector::OneVector, true, EPSCPoolMethod::AutoRelease);
	}
	if (ensure(ImpactSound)) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, SweepResult.ImpactPoint);
	}
	GetWorld()->DestroyActor(this);
}

void AARPrimaryMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
//	sphere_comp->OnComponentHit.AddDynamic(this, &AARPrimaryMagicProjectile::OnHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AARPrimaryMagicProjectile::OnOverlap);
}
