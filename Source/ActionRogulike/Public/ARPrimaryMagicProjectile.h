// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionRogulike/ARMagicProjectile.h"
#include "ARPrimaryMagicProjectile.generated.h"

/**
 *
 */
UCLASS()
class ACTIONROGULIKE_API AARPrimaryMagicProjectile final : public AARMagicProjectile
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	class UParticleSystem* ParticleOnDestroy;
	UPROPERTY(EditAnywhere)
	class USoundBase* ImpactSound;
public:
	AARPrimaryMagicProjectile();
	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComponent,
	//	AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
