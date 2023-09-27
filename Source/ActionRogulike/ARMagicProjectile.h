#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARMagicProjectile.generated.h"

UCLASS()
class ACTIONROGULIKE_API AARMagicProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AARMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* MovementComp;
	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComp;
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystem;
};
