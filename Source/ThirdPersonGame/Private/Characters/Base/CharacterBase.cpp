#include "Characters/Base/CharacterBase.h"

#include "Const.h"
#include "AbilitySystem/Abilities/CharacterAbility.h"
#include "AbilitySystem/Attributes/CharacterAttributeSet.h"
#include "AbilitySystem/Component/CharacterAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Enumerations/CharacterAbilityID.h"

ACharacterBase::ACharacterBase()
{
	//PrimaryActorTick.bCanEverTick = true;
	bAlwaysRelevant = true;

	AttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("Attribute Set"));
	AttributeSet->HealthChangedDelegate.AddUObject(this, &ACharacterBase::OnHealthChanged);
	AttributeSet->MaxHealthChangedDelegate.AddUObject(this, &ACharacterBase::OnMaxHealthChanged);
	AttributeSet->ManaChangedDelegate.AddUObject(this, &ACharacterBase::OnManaChanged);
	AttributeSet->MaxManaChangedDelegate.AddUObject(this, &ACharacterBase::OnMaxManaChanged);
	AttributeSet->StaminaChangedDelegate.AddUObject(this, &ACharacterBase::OnStaminaChanged);
	AttributeSet->MaxStaminaChangedDelegate.AddUObject(this, &ACharacterBase::OnMaxStaminaChanged);
	AttributeSet->BaseDamageChangedDelegate.AddUObject(this, &ACharacterBase::OnBaseDamageChanged);
	AttributeSet->CharacterTimeDilationChangedDelegate.AddUObject(this, &ACharacterBase::OnCharacterTimeDilationChanged);
	AttributeSet->CharacterLevelChangedDelegate.AddUObject(this, &ACharacterBase::OnCharacterLevelChanged);

	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>("Ability System");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void ACharacterBase::AddCharacterAttributes()
{
}

void ACharacterBase::InitializeStartupEffects()
{
	for (const TSubclassOf<UGameplayEffect> StartupEffect : StartupEffects)
	{
		ApplyGameplayEffect(StartupEffect);
	}
}

void ACharacterBase::ApplyGameplayEffect(const TSubclassOf<UGameplayEffect> Effect) const
{
	if (!HasAuthority()) return;

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	if (const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, AttributeSet->GetCharacterLevel(), EffectContextHandle); EffectSpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), AbilitySystemComponent);
	}
}

void ACharacterBase::InitializeStartupAttributes()
{
	ApplyGameplayEffect(StartupAttributesEffect);
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	InitializeStartupAttributes();
	InitializeStartupEffects();
}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeInherentAbilities();
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

#pragma region Ability System
UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

bool ACharacterBase::IsAlive() const
{
	return AttributeSet->GetHealth() > 0;
}

void ACharacterBase::GiveGameplayAbility(TSubclassOf<UCharacterAbility> AbilityClass, const uint8 InAbilityLevel)
{
	if (!HasAuthority()) return;

	/*const UCharacterAbility* Ability = AbilityClass.GetDefaultObject();
	const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(
		AbilityClass,
		GetAbilityLevel(Ability->GetAbilityID()),
		Ability->GetAbilityInputID(),
		this);
	AbilitySystemComponent->GiveAbility(AbilitySpec);

	AttributeSet->SetHealth(100);*/

	AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass, InAbilityLevel, INDEX_NONE, this));
}

void ACharacterBase::InitializeInherentAbilities()
{
	for (const TSubclassOf<UCharacterAbility> InherentAbility : CharacterAbilities)
	{
		GiveGameplayAbility(InherentAbility, GetAbilityLevel(ECharacterAbilityID::None));
	}
}

int8 ACharacterBase::GetAbilityLevel(const ECharacterAbilityID AbilityInputId) const
{
	return StartupAttributesEffectLevel;
}

void ACharacterBase::RemoveCharacterAbilities()
{
	if (!HasAuthority()) return;

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;

	for (const FGameplayAbilitySpec AbilitySpec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if (AbilitySpec.SourceObject == this && CharacterAbilities.Contains(AbilitySpec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(AbilitySpec.Handle);
		}
	}

	for (FGameplayAbilitySpecHandle AbilitySpecHandle : AbilitiesToRemove)
	{
		AbilitySystemComponent->ClearAbility(AbilitySpecHandle);
	}
}
#pragma endregion

void ACharacterBase::Die()
{
	CharacterDeathDelegate.Broadcast(this);
	RemoveCharacterAbilities();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AbilitySystemComponent->CancelAbilities();
	FGameplayTagContainer EffectsRemovedTagContainer;
	EffectsRemovedTagContainer.AddTag(FConst::EffectsRemovedOnDeadTagConst);
	int32 NumEffectsRemoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectsRemovedTagContainer);
	AbilitySystemComponent->AddLooseGameplayTag(FConst::DeadTagConst);

	if (DeathAnimMontage)
	{
		PlayAnimMontage(DeathAnimMontage);
		return;
	}

	FinishDying();
}

void ACharacterBase::FinishDying()
{
	Destroy();
}

#pragma region Attribute Functions
float ACharacterBase::GetHealth() const
{
	return AttributeSet->GetHealth();
}

void ACharacterBase::SetHealth(const float InHealth) const
{
	AttributeSet->SetHealth(InHealth);
}

void ACharacterBase::InitHealth(const float InHealth) const
{
	AttributeSet->InitHealth(InHealth);
}

float ACharacterBase::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

void ACharacterBase::SetMaxHealth(const float InMaxHealth) const
{
	AttributeSet->SetMaxHealth(InMaxHealth);
}

void ACharacterBase::InitMaxHealth(const float InMaxHealth) const
{
	AttributeSet->InitMaxHealth(InMaxHealth);
}

float ACharacterBase::GetMana() const
{
	return AttributeSet->GetMana();
}

void ACharacterBase::SetMana(const float InMana) const
{
	AttributeSet->SetMana(InMana);
}

void ACharacterBase::InitMana(const float InMana) const
{
	AttributeSet->InitMana(InMana);
}

float ACharacterBase::GetMaxMana() const
{
	return AttributeSet->GetMaxMana();
}

void ACharacterBase::SetMaxMana(const float InMaxMana) const
{
	AttributeSet->SetMaxMana(InMaxMana);
}

void ACharacterBase::InitMaxMana(const float InMaxMana) const
{
	AttributeSet->InitMaxMana(InMaxMana);
}

float ACharacterBase::GetStamina() const
{
	return AttributeSet->GetStamina();
}

void ACharacterBase::SetStamina(const float InStamina) const
{
	AttributeSet->SetStamina(InStamina);
}

void ACharacterBase::InitStamina(const float InStamina) const
{
	AttributeSet->InitStamina(InStamina);
}

float ACharacterBase::GetMaxStamina() const
{
	return AttributeSet->GetMaxStamina();
}

void ACharacterBase::SetMaxStamina(const float InMaxStamina) const
{
	AttributeSet->SetMaxStamina(InMaxStamina);
}

void ACharacterBase::InitMaxStamina(const float InMaxStamina) const
{
	AttributeSet->InitMaxStamina(InMaxStamina);
}

float ACharacterBase::GetCharacterLevel() const
{
	return AttributeSet->GetCharacterLevel();
}

void ACharacterBase::SetCharacterLevel(const float InLevel) const
{
	AttributeSet->SetCharacterLevel(InLevel);
}

void ACharacterBase::InitCharacterLevel(const float InLevel) const
{
	AttributeSet->InitCharacterLevel(InLevel);
}
#pragma endregion


#pragma region Attribute Changed Handles
void ACharacterBase::OnHealthChanged_Implementation(const float AttributeValue, const int32 EffectStackCount)
{
	//if (ShowAttributeChangedMessage)
	//{
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3, FColor::Green, TEXT("Health Changed!"));
	//}
}

void ACharacterBase::OnMaxHealthChanged_Implementation(const float AttributeValue, const int32 EffectStackCount)
{
	//if (ShowAttributeChangedMessage)
	//{
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3, FColor::Green, TEXT("MaxHealth Changed!"));
	//}
}

void ACharacterBase::OnManaChanged_Implementation(const float AttributeValue, const int32 EffectStackCount)
{
	//if (ShowAttributeChangedMessage)
	//{
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3, FColor::Green, TEXT("Mana Changed!"));
	//}
}

void ACharacterBase::OnMaxManaChanged_Implementation(const float AttributeValue, const int32 EffectStackCount)
{
	//if (ShowAttributeChangedMessage)
	//{
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3, FColor::Green, TEXT("MaxMana Changed!"));
	//}
}

void ACharacterBase::OnStaminaChanged_Implementation(const float AttributeValue, const int32 EffectStackCount)
{
	//if (ShowAttributeChangedMessage)
	//{
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3, FColor::Green, TEXT("Stamina Changed!"));
	//}
}

void ACharacterBase::OnMaxStaminaChanged_Implementation(const float AttributeValue, const int32 EffectStackCount)
{
	//if (ShowAttributeChangedMessage)
	//{
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3, FColor::Green, TEXT("MaxStamina Changed!"));
	//}
}

void ACharacterBase::OnBaseDamageChanged_Implementation(const float AttributeValue, const int32 EffectStackCount)
{
	//if (ShowAttributeChangedMessage)
	//{
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3, FColor::Green, TEXT("BaseDamage Changed!"));
	//}
}

void ACharacterBase::OnCharacterTimeDilationChanged_Implementation(const float AttributeValue, const int32 EffectStackCount)
{
	if (ShowAttributeChangedMessage)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3, FColor::Green, FString::Printf(TEXT("TimeDilation Changed: %f"), AttributeValue));
	}
}

void ACharacterBase::OnCharacterLevelChanged_Implementation(const float AttributeValue, const int32 EffectStackCount)
{
	//if (ShowAttributeChangedMessage)
	//{
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3, FColor::Green, TEXT("Level Changed!"));
	//}
}

void ACharacterBase::OnStunChanged_Implementation(const FGameplayTag CallbackTag, const int32 NewCount)
{
	if (NewCount > 0)
	{
		FGameplayTagContainer AbilitiesRemovedOnStunTagContainer;
		AbilitiesRemovedOnStunTagContainer.AddTag(FConst::AbilityTagConst);

		FGameplayTagContainer AbilitiesNotRemovedTagContainer;
		AbilitiesNotRemovedTagContainer.AddTag(FConst::AbilityNotRemoveOnStunConst);

		AbilitySystemComponent->CancelAbilities(&AbilitiesRemovedOnStunTagContainer, &AbilitiesNotRemovedTagContainer);
	}
}
#pragma endregion
