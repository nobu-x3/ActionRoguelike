#include "ARCharacter.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "ActionRogulike/ARMagicProjectile.h"
#include "ARInteractComponent.h"
#include "AttributeComponent.h"

// Sets default values
AARCharacter::AARCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	InteractComp = CreateDefaultSubobject<UARInteractComponent>("Interact component");
	AttributeComp = CreateDefaultSubobject<UAttributeComponent>("Attribute component");
}

void AARCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &AARCharacter::OnHealthChanged);
}

void AARCharacter::Move(const FInputActionInstance& Instance)
{
	auto rot = GetControlRotation();
	rot.Pitch = 0.0f;
	rot.Roll = 0.0f;
	const FVector2D val = Instance.GetValue().Get<FVector2D>();
	AddMovementInput(rot.Vector(), val.Y);
	const FVector right_vec = FRotationMatrix(rot).GetScaledAxis(EAxis::Y);
	AddMovementInput(right_vec, val.X);
}

void AARCharacter::LookMouse(const FInputActionInstance& Instance)
{
	const FVector2D val = Instance.GetValue().Get<FVector2D>();
	AddControllerPitchInput(-val.Y);
	AddControllerYawInput(val.X);
}

void AARCharacter::PrimaryAttack(const FInputActionInstance& Instance)
{
	FTimerHandle anim_delay;
	GetWorld()->GetTimerManager().SetTimer(anim_delay, this, &AARCharacter::PrimaryAttack_DelayElapsed, 0.25f);
	PlayAnimMontage(PrimaryAttackAnim);
}

void AARCharacter::SecondaryAttack(const FInputActionInstance& Instance)
{
	FTimerHandle anim_delay;
	GetWorld()->GetTimerManager().SetTimer(anim_delay, this, &AARCharacter::SecondaryAttack_DelayElapsed, 0.25f);
	PlayAnimMontage(PrimaryAttackAnim);
}

void AARCharacter::PrimaryAttack_DelayElapsed() {
	AActor* owner = GetOwner();
	auto cam_tr = Camera->GetComponentTransform();
	FVector end =
		cam_tr.GetLocation() + (cam_tr.GetRotation().Vector() * 100000.f);
	FCollisionQueryParams query_params;
	query_params.AddIgnoredActor(this);
	FTransform spawn_tr = FTransform(GetControlRotation(), GetMesh()->GetSocketLocation("Muzzle_01"));
	FHitResult hit;
	FActorSpawnParameters spawn_params;
	spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawn_params.Instigator = this;
	auto bHit = GetWorld()->LineTraceSingleByChannel(hit, cam_tr.GetLocation(), end, ECC_Visibility, query_params);
	if (bHit) {
		auto rot = FRotationMatrix::MakeFromX(hit.ImpactPoint - spawn_tr.GetLocation()).Rotator();
		GetWorld()->SpawnActor<AActor>(PrimaryProjectileClass, spawn_tr.GetLocation(), rot, spawn_params);
	}
	else {
		GetWorld()->SpawnActor<AActor>(PrimaryProjectileClass, spawn_tr, spawn_params);
	}
}

void AARCharacter::SecondaryAttack_DelayElapsed()
{
	AActor* owner = GetOwner();
	auto cam_tr = Camera->GetComponentTransform();
	FVector end =
		cam_tr.GetLocation() + (cam_tr.GetRotation().Vector() * 100000.f);
	FCollisionQueryParams query_params;
	query_params.AddIgnoredActor(this);
	FTransform spawn_tr = FTransform(GetControlRotation(), GetMesh()->GetSocketLocation("Muzzle_01"));
	FHitResult hit;
	FActorSpawnParameters spawn_params;
	spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawn_params.Instigator = this;
	auto bHit = GetWorld()->LineTraceSingleByChannel(hit, cam_tr.GetLocation(), end, ECC_Visibility, query_params);
	if (bHit) {
		auto rot = FRotationMatrix::MakeFromX(hit.ImpactPoint - spawn_tr.GetLocation()).Rotator();
		GetWorld()->SpawnActor<AActor>(SecondaryProjectileClass, spawn_tr.GetLocation(), rot, spawn_params);
	}
	else {
		GetWorld()->SpawnActor<AActor>(SecondaryProjectileClass, spawn_tr, spawn_params);
	}
}

void AARCharacter::OnHealthChanged(AActor* HealthChangeInstigator, UAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (!AttributeComp->IsAlive()) return;
	if (Delta < 0) {
		GetMesh()->SetScalarParameterValueOnMaterials("HitTimestamp", GetWorld()->TimeSeconds);
	}
	if (NewHealth <= 0) {
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}

void AARCharacter::Interact(const FInputActionInstance& Instance)
{
	InteractComp->PrimaryInteract();
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
	const APlayerController* pc = GetController<APlayerController>();
	const ULocalPlayer* lp = pc->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* subsystem = lp->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(subsystem);
	subsystem->AddMappingContext(DefaultInputMapping, 0);
	UEnhancedInputComponent* input_comp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	input_comp->BindAction(InputMove, ETriggerEvent::Triggered, this, &AARCharacter::Move);
	input_comp->BindAction(InputLookMouse, ETriggerEvent::Triggered, this, &AARCharacter::LookMouse);
	input_comp->BindAction(InputPrimaryAttack, ETriggerEvent::Started, this, &AARCharacter::PrimaryAttack);
	input_comp->BindAction(InputSecondaryAttack, ETriggerEvent::Started, this, &AARCharacter::SecondaryAttack);
	input_comp->BindAction(InputInteract, ETriggerEvent::Started, this, &AARCharacter::Interact);
}

