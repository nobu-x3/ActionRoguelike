#include "ARMagicProjectile.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>

// Sets default values
AARMagicProjectile::AARMagicProjectile()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("Movement Component");
	SphereComp = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	SetRootComponent(SphereComp);
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("Particle Component");
	ParticleSystem->SetupAttachment(SphereComp);
}

// Called when the game starts or when spawned
void AARMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AARMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
