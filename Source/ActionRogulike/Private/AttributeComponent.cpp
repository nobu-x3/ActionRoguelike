// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"


// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	health = 100.f;
}

bool UAttributeComponent::ApplyHealthDelta(float delta)
{
	health += delta;
	return true;
}
