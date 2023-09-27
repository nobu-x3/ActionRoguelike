// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARCharacter.generated.h"

class UInputAction;
UCLASS()
class ACTIONROGULIKE_API AARCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UARInteractComponent* InteractComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAttributeComponent* AttributeComp;

private:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<class AARMagicProjectile> PrimaryProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<class AARMagicProjectile> SecondaryProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* PrimaryAttackAnim;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* DefaultInputMapping;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InputMove;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InputLookMouse;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InputJump;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InputPrimaryAttack;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InputSecondaryAttack;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InputInteract;
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

public:
	// Sets default values for this character's properties
	AARCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void Move(const struct FInputActionInstance& Instance);
	void LookMouse(const struct FInputActionInstance& Instance);
	void PrimaryAttack(const struct FInputActionInstance& Instance);
	void SecondaryAttack(const struct FInputActionInstance& Instance);
	void Interact(const struct FInputActionInstance& Instance);
	void PrimaryAttack_DelayElapsed();
	void SecondaryAttack_DelayElapsed();
	UFUNCTION()
	void OnHealthChanged(AActor* HealthChangeInstigator, class UAttributeComponent* OwningComp, float NewHealth, float Delta);
};
