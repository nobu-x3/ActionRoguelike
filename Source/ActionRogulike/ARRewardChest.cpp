#include "ARRewardChest.h"

// Sets default values
AARRewardChest::AARRewardChest()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	SetRootComponent(body);
	lid = CreateDefaultSubobject<UStaticMeshComponent>("Lid");
	lid->SetupAttachment(body);
}

void AARRewardChest::Interact_Implementation(APawn* instigator)
{
	lid->SetRelativeRotation(FRotator(110.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AARRewardChest::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AARRewardChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
