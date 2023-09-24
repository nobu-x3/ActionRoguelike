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

private:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<class AARMagicProjectile> primary_projectile_class;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<class AARMagicProjectile> secondary_projectile_class;
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* primary_attack_anim;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* default_input_mapping;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* input_move;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* input_look_mouse;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* input_jump;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* input_primary_attack;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* input_secondary_attack;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* input_interact;
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* spring_arm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* camera;
	UPROPERTY(VisibleAnywhere)
	class UARInteractComponent* interact_comp;
	UPROPERTY(VisibleAnywhere)
	class UAttributeComponent* attribute_comp;

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
};
