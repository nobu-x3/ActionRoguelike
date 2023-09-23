#include "ARMagicProjectile.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>

// Sets default values
AARMagicProjectile::AARMagicProjectile()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	movement_comp = CreateDefaultSubobject<UProjectileMovementComponent>("Movement Component");
	sphere_comp = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	sphere_comp->SetCollisionProfileName("Projectile");
	sphere_comp->IgnoreActorWhenMoving(GetInstigator(), true);
	SetRootComponent(sphere_comp);
	particle_system = CreateDefaultSubobject<UParticleSystemComponent>("Particle Component");
	particle_system->SetupAttachment(sphere_comp);
}

// Called when the game starts or when spawned
void AARMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	sphere_comp->OnComponentHit.AddDynamic(this, &AARMagicProjectile::OnHit);
}


void AARMagicProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorld()->DestroyActor(this);
}

// Called every frame
void AARMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
