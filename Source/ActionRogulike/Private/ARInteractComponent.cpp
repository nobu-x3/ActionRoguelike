// Fill out your copyright notice in the Description page of Project Settings.


#include "ARInteractComponent.h"
#include <ARInteractionInterface.h>

// Sets default values for this component's properties
UARInteractComponent::UARInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UARInteractComponent::PrimaryInteract()
{
	AActor* owner = GetOwner();
	FVector eye_loc;
	FRotator eye_rot;
	owner->GetActorEyesViewPoint(eye_loc, eye_rot);
	FVector end = eye_loc + (eye_rot.Vector() * range);
	FCollisionObjectQueryParams query_params;
	query_params.AddObjectTypesToQuery(ECC_WorldDynamic);
	TArray<FHitResult> hits;
	FColor dbg_color = FColor::Yellow;
	FCollisionShape sphere;
	sphere.SetSphere(30.0f);
	if (GetWorld()->SweepMultiByObjectType(hits, eye_loc, end, FQuat::Identity, query_params, sphere)) {
		for (FHitResult hit : hits) {
			AActor* hit_actor = hit.GetActor();
			if (hit_actor) {
				bool bImplements = hit_actor->GetClass()->ImplementsInterface(UARInteractionInterface::StaticClass());
				if (bImplements) {
					APawn* instigator = Cast<APawn>(owner);
					IARInteractionInterface::Execute_Interact(hit_actor, instigator);
					dbg_color = FColor::Green;
				}
			}
		}
	}
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), eye_loc, end, DrawScale, dbg_color, false, 1.0f, 0, Thickness);
}


// Called when the game starts
void UARInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UARInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

