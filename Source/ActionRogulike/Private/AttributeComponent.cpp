// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"


// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	Health = 100.f;
}

bool UAttributeComponent::ApplyHealthDelta(AActor* Instigator, float delta)
{
	Health += delta;
	OnHealthChanged.Broadcast(Instigator, this, Health, delta);
	return true;
}
