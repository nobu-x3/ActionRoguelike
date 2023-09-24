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

//void AARPrimaryMagicProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	if (OtherActor) {
//		UAttributeComponent* attrib_comp = Cast<UAttributeComponent>(OtherActor->GetComponentByClass(UAttributeComponent::StaticClass()));
//		if (attrib_comp) {
//			attrib_comp->ApplyHealthDelta(-20.0f);
//		}
//	}
//	if (ensure(destroy_particle)) {
//		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), destroy_particle, Hit.ImpactPoint, FRotator::ZeroRotator, FVector::OneVector, true, EPSCPoolMethod::AutoRelease);
//	}
//	GetWorld()->DestroyActor(this);
//}

void AARPrimaryMagicProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* instigator = Cast<AActor>(GetInstigator());
	if (instigator == OtherActor) return;
	if (OtherActor) {
		UAttributeComponent* attrib_comp = Cast<UAttributeComponent>(OtherActor->GetComponentByClass(UAttributeComponent::StaticClass()));
		if (attrib_comp) {
			attrib_comp->ApplyHealthDelta(-20.0f);
		}
	}
	if (ensure(destroy_particle)) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), destroy_particle, SweepResult.ImpactPoint, FRotator::ZeroRotator, FVector::OneVector, true, EPSCPoolMethod::AutoRelease);
	}
	GetWorld()->DestroyActor(this);
}

void AARPrimaryMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
//	sphere_comp->OnComponentHit.AddDynamic(this, &AARPrimaryMagicProjectile::OnHit);
	sphere_comp->OnComponentBeginOverlap.AddDynamic(this, &AARPrimaryMagicProjectile::OnOverlap);
}
