#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>
#include "Public/ARInteractionInterface.h"
#include <ARRewardChest.generated.h>


UCLASS()
class ACTIONROGULIKE_API AARRewardChest : public AActor, public IARInteractionInterface
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Lid;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Body;

public:
	// Sets default values for this actor's properties
	AARRewardChest();

	virtual void Interact_Implementation(APawn* instigator) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
