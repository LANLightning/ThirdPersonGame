// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	public: \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \

DECLARE_MULTICAST_DELEGATE_TwoParams(FAttributeValueChange, const float, const int32)

UCLASS()
class THIRDPERSONGAME_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "CharacterAttributeSet|Health", ReplicatedUsing = OnReplicateHealth, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Health;
	
	UPROPERTY(BlueprintReadOnly, Category = "CharacterAttributeSet|Health", ReplicatedUsing = OnReplicateMaxHealth, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterAttributeSet|Mana", ReplicatedUsing = OnReplicateMana, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterAttributeSet|Mana", ReplicatedUsing = OnReplicateMaxMana, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterAttributeSet|Stamina", ReplicatedUsing = OnReplicateStamina, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Stamina;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterAttributeSet|Stamina", ReplicatedUsing = OnReplicateMaxStamina, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxStamina;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterAttributeSet|BaseDamage", ReplicatedUsing = OnReplicateBaseDamage, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData BaseDamage;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterAttributeSet|CharacterTimeDilation", ReplicatedUsing = OnReplicateTimeDilation, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData CharacterTimeDilation;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterAttributeSet|CharacterLevel", ReplicatedUsing = OnReplicateLevel, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData CharacterLevel;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterAttributeSet|MetaAttributes", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData DamageTaken;

	UFUNCTION()
	virtual void OnReplicateHealth(const FGameplayAttributeData& PreviousHealth)
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, Health, PreviousHealth);
	}

	UFUNCTION()
	virtual void OnReplicateMaxHealth(const FGameplayAttributeData& PreviousMaxHealth)
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, MaxHealth, PreviousMaxHealth);
	}

	UFUNCTION()
	virtual void OnReplicateMana(const FGameplayAttributeData& PreviousMana)
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, Mana, PreviousMana);
	}

	UFUNCTION()
	virtual void OnReplicateMaxMana(const FGameplayAttributeData& PreviousMaxMana)
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, MaxMana, PreviousMaxMana);
	}

	UFUNCTION()
	virtual void OnReplicateStamina(const FGameplayAttributeData& PreviousStamina)
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, Stamina, PreviousStamina);
	}

	UFUNCTION()
	virtual void OnReplicateMaxStamina(const FGameplayAttributeData& PreviousMaxStamina)
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, MaxStamina, PreviousMaxStamina);
	}

	UFUNCTION()
	virtual void OnReplicateTimeDilation(const FGameplayAttributeData& PreviousTimeDilation)
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, CharacterTimeDilation, PreviousTimeDilation);
	}

	UFUNCTION()
	virtual void OnReplicateBaseDamage(const FGameplayAttributeData& PreviousBaseDamage)
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, BaseDamage, PreviousBaseDamage);
	}

	UFUNCTION()
	virtual void OnReplicateLevel(const FGameplayAttributeData& PreviousLevel)
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, CharacterLevel, PreviousLevel);
	}

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxMana);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Stamina);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxStamina);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, BaseDamage);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, CharacterTimeDilation);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, CharacterLevel);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, DamageTaken);

public:
	FAttributeValueChange HealthChangedDelegate;
	FAttributeValueChange MaxHealthChangedDelegate;
	FAttributeValueChange ManaChangedDelegate;
	FAttributeValueChange MaxManaChangedDelegate;
	FAttributeValueChange StaminaChangedDelegate;
	FAttributeValueChange MaxStaminaChangedDelegate;
	FAttributeValueChange BaseDamageChangedDelegate;
	FAttributeValueChange CharacterTimeDilationChangedDelegate;
	FAttributeValueChange CharacterLevelChangedDelegate;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

};
