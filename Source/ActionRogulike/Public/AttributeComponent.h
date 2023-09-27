// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, Instigator, UAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGULIKE_API UAttributeComponent final : public UActorComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Health;
public:	
	UAttributeComponent();
	UFUNCTION(BlueprintCallable)
	bool ApplyHealthDelta(AActor* actor, float delta);
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
};
