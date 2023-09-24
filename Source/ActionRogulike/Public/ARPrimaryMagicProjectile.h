// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionRogulike/ARMagicProjectile.h"
#include "ARPrimaryMagicProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGULIKE_API AARPrimaryMagicProjectile : public AARMagicProjectile
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	class UParticleSystem* destroy_particle;
public:	
	AARPrimaryMagicProjectile();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
