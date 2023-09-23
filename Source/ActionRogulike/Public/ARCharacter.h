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
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AARMagicProjectile> primary_projectile_class;
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
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* spring_arm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* camera;

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

};
