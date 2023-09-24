// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGULIKE_API UAttributeComponent final : public UActorComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float health;
public:	
	UAttributeComponent();
	UFUNCTION(BlueprintCallable)
	bool ApplyHealthDelta(float delta);
	// Sets default values for this component's properties
};
