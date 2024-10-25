// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

struct FGameplayTag;
struct FOnAttributeChangeData;
class UCharacterAttributeSet;
class UCharacterAbilitySystemComponent;
class UGameplayEffect;
class UCharacterAbility;

enum class ECharacterAbilityID :uint8;
//enum class ECharacterAbilityInputID : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDeathDelegate, ACharacterBase*, Character);

UCLASS()
class THIRDPERSONGAME_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Ability System|DEBUG")
	bool ShowAttributeChangedMessage;

public:
	UPROPERTY(BlueprintAssignable, Category = "Character")
	FCharacterDeathDelegate CharacterDeathDelegate;

	ACharacterBase();

protected:
	UPROPERTY(VisibleAnywhere)
	UCharacterAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	UCharacterAttributeSet* AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System")
	TArray<TSubclassOf<UCharacterAbility>> CharacterAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System")
	TSubclassOf<UGameplayEffect> StartupAttributesEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	FText CharacterName = FText::FromString("Character Name");

	const int StartupAttributesEffectLevel = 1;
	void GiveGameplayAbility(TSubclassOf<UCharacterAbility> AbilityClass, const uint8 InAbilityLevel);
	void ApplyGameplayEffect(const TSubclassOf<UGameplayEffect> Effect) const;
	virtual void AddCharacterAttributes();
	virtual void InitializeInherentAbilities();
	virtual void InitializeStartupEffects();
	virtual void InitializeStartupAttributes();
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual bool IsAlive() const;

	virtual int8 GetAbilityLevel(const ECharacterAbilityID AbilityId) const;

	virtual void RemoveCharacterAbilities();

	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual void FinishDying();

#pragma region Attribute Functions
	UFUNCTION(BlueprintPure, Category = "Attribute")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetHealth(const float InHealth) const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void InitHealth(const float InHealth) const;

	UFUNCTION(BlueprintPure, Category = "Attribute")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetMaxHealth(const float InMaxHealth) const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void InitMaxHealth(const float InMaxHealth) const;

	UFUNCTION(BlueprintPure, Category = "Attribute")
	float GetMana() const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetMana(const float InMana) const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void InitMana(const float InMana) const;

	UFUNCTION(BlueprintPure, Category = "Attribute")
	float GetMaxMana() const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetMaxMana(const float InMaxMana) const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void InitMaxMana(const float InMaxMana) const;

	UFUNCTION(BlueprintPure, Category = "Attribute")
	float GetStamina() const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetStamina(const float InStamina) const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void InitStamina(const float InStamina) const;

	UFUNCTION(BlueprintPure, Category = "Attribute")
	float GetMaxStamina() const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetMaxStamina(const float InMaxStamina) const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void InitMaxStamina(const float InMaxStamina) const;

	UFUNCTION(BlueprintPure, Category = "Attribute")
	float GetCharacterLevel() const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetCharacterLevel(const float InLevel) const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void InitCharacterLevel(const float InLevel) const;
#pragma endregion

#pragma region Attribute Changed Handles
	//FDelegateHandle HealthChangeDelegateHandle;
	//FDelegateHandle MaxHealthChangeDelegateHande;
	//FDelegateHandle ManaChangeDelegateHandle;
	//FDelegateHandle MaxManaChangeDelegateHande;
	//FDelegateHandle StaminaChangeDelegateHandle;
	//FDelegateHandle MaxStaminaChangeDelegateHandle;
	//FDelegateHandle BaseDamageChangeDelegateHandle;
	//FDelegateHandle TimeDilationChangeDelegateHandle;
	//FDelegateHandle LevelChangeDelegateHandle;

	UFUNCTION(BlueprintNativeEvent)
	void OnHealthChanged(const float AttributeValue, const int32 EffectStackCount);
	UFUNCTION(BlueprintNativeEvent)
	void OnMaxHealthChanged(const float AttributeValue, const int32 EffectStackCount);

	UFUNCTION(BlueprintNativeEvent)
	void OnManaChanged(const float AttributeValue, const int32 EffectStackCount);
	UFUNCTION(BlueprintNativeEvent)
	void OnMaxManaChanged(const float AttributeValue, const int32 EffectStackCount);

	UFUNCTION(BlueprintNativeEvent)
	void OnStaminaChanged(const float AttributeValue, const int32 EffectStackCount);
	UFUNCTION(BlueprintNativeEvent)
	void OnMaxStaminaChanged(const float AttributeValue, const int32 EffectStackCount);

	UFUNCTION(BlueprintNativeEvent)
	void OnBaseDamageChanged(const float AttributeValue, const int32 EffectStackCount);
	UFUNCTION(BlueprintNativeEvent)
	void OnCharacterTimeDilationChanged(const float AttributeValue, const int32 EffectStackCount);

	UFUNCTION(BlueprintNativeEvent)
	void OnCharacterLevelChanged(const float AttributeValue, const int32 EffectStackCount);
	UFUNCTION(BlueprintNativeEvent)
	void OnStunChanged(const FGameplayTag CallbackTag, const int32 NewCount);
#pragma endregion
};
