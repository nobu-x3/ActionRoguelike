#include "ARRewardChest.h"

// Sets default values
AARRewardChest::AARRewardChest()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	SetRootComponent(Body);
	Lid = CreateDefaultSubobject<UStaticMeshComponent>("Lid");
	Lid->SetupAttachment(Body);
}

void AARRewardChest::Interact_Implementation(APawn* instigator)
{
	Lid->SetRelativeRotation(FRotator(110.f, 0.f, 0.f));
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
