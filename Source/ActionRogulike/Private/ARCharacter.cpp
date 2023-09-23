// Fill out your copyright notice in the Description page of Project Settings.


#include "ARCharacter.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>


// Sets default values
AARCharacter::AARCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	spring_arm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	spring_arm->SetupAttachment(RootComponent);
	spring_arm->bUsePawnControlRotation = true;
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->SetupAttachment(spring_arm);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AARCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AARCharacter::MoveForward(float val)
{
	auto rot = GetControlRotation();
	rot.Pitch = 0.0f;
	rot.Roll = 0.0f;
	AddMovementInput(rot.Vector(), val);
}

void AARCharacter::MoveRight(float val)
{
	auto rot = GetControlRotation();
	rot.Pitch = 0.0f;
	rot.Roll = 0.0f;
	auto right_vec = FRotationMatrix(rot).GetScaledAxis(EAxis::Y);
	AddMovementInput(right_vec, val);
}

// Called every frame
void AARCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}

// Called to bind functionality to input
void AARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AARCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AARCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookYaw", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookPitch", this, &APawn::AddControllerPitchInput);
}

