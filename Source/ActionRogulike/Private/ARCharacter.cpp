// Fill out your copyright notice in the Description page of Project Settings.


#include "ARCharacter.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>


// Sets default values
AARCharacter::AARCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	spring_arm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	spring_arm->SetupAttachment(RootComponent);
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->SetupAttachment(spring_arm);
}

// Called when the game starts or when spawned
void AARCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AARCharacter::MoveForward(float val)
{
	AddMovementInput(GetActorForwardVector(), val);
}

void AARCharacter::MoveRight(float val)
{
	AddMovementInput(GetActorRightVector(), val);
}

// Called every frame
void AARCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AARCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AARCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Look", this, &APawn::AddControllerYawInput);
}

