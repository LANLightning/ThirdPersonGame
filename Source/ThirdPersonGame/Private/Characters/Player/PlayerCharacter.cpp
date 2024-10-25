// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/PlayerCharacter.h"

#include "MathUtil.h"
#include "AbilitySystem/Attributes/CharacterAttributeSet.h"
#include "AbilitySystem/Component/CharacterAbilitySystemComponent.h"
#include "AI/Controllers/PlayerAIController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	SpringArmComponent->TargetArmLength = 100;
	SpringArmComponent->SocketOffset = FVector(-250.0f, 0.0f, 150.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->SetRelativeRotation(FRotator(0.0f, -10.0f, 0.0f));

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName(TEXT("NoCollision")));
	AIControllerClass = APlayerAIController::StaticClass();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultSpringArmLength = SpringArmComponent->TargetArmLength;
	DefaultSpringArmRelativeLocation = SpringArmComponent->GetRelativeLocation();

	//InitializeInherentAbilities();
	//InitializeStartupEffects();
	//InitializeStartupAttributes();

	//InitializeLevel(DefaultLevel);
	//InitializeHealth(DefaultMaxHealth, DefaultMaxHealth);
	//InitializeMana(DefaultMaxMana, DefaultMaxMana);
	//InitializeStamina(DefaultMaxStamina, DefaultMaxStamina);
}

#pragma region Player Input Functions
void APlayerCharacter::Look(const FVector2D& InputValue)
{
	AddControllerYawInput(InputValue.X);
	AddControllerPitchInput(InputValue.Y);
}

void APlayerCharacter::Zoom(float InputValue)
{
	SpringArmComponent->TargetArmLength += InputValue;
	SpringArmComponent->TargetArmLength = FMathf::Clamp(SpringArmComponent->TargetArmLength, 150, 750);
	CameraComponent->bUsePawnControlRotation = true;
}

void APlayerCharacter::Move(const FVector2D& InputValue)
{
	const FVector RightDirection = GetControlRotation().RotateVector(FVector::RightVector);
	const FVector ForwardDirection = GetControlRotation().RotateVector(FVector::ForwardVector);

	AddMovementInput(RightDirection, InputValue.X);
	AddMovementInput(ForwardDirection, InputValue.Y);
}
#pragma endregion

#pragma region Helper Functions
void APlayerCharacter::InitializeLevel(const uint16 InLevel) const
{
	AttributeSet->SetCharacterLevel(InLevel);
}

void APlayerCharacter::InitializeHealth(const float InHealth, const float InMaxHealth) const
{
	AttributeSet->SetMaxHealth(InMaxHealth);
	AttributeSet->SetHealth(InHealth);
}

void APlayerCharacter::InitializeMana(const float InMana, const float InMaxMana) const
{
	AttributeSet->SetMaxMana(InMaxMana);
	AttributeSet->SetMana(InMana);
}

void APlayerCharacter::InitializeStamina(const float InStamina, const float InMaxStamina) const
{
	AttributeSet->SetMaxStamina(InMaxStamina);
	AttributeSet->SetStamina(InStamina);
}
#pragma endregion

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//InitializeAbilitySystem();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//InitializeAbilitySystem();

	DefaultPlayerController = Cast<ADefaultPlayerController>(NewController);
}

void APlayerCharacter::Die()
{
	Super::Die();

	if (!DefaultPlayerController) return;
	DefaultPlayerController->DisableInput(DefaultPlayerController);
}
