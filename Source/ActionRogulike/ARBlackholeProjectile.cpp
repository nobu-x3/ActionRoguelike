#include "ARBlackholeProjectile.h"
#include <PhysicsEngine/RadialForceComponent.h>
#include <Components/SphereComponent.h>
// Sets default values
AARBlackholeProjectile::AARBlackholeProjectile()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	radial_force = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	radial_force->bIgnoreOwningActor = true;
	sphere_comp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
}

// Called when the game starts or when spawned
void AARBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AARBlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
