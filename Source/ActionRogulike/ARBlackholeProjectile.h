#pragma once

#include "CoreMinimal.h"
#include "ARMagicProjectile.h"
#include "ARBlackholeProjectile.generated.h"

UCLASS()
class ACTIONROGULIKE_API AARBlackholeProjectile final: public AARMagicProjectile
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class URadialForceComponent* RadialForce;

public:
	// Sets default values for this actor's properties
	AARBlackholeProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
