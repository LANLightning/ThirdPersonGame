#include "AbilitySystem/Attributes/CharacterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "MathUtil.h"
#include "Net/UnrealNetwork.h"

void UCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, CharacterTimeDilation, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, BaseDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, CharacterLevel, COND_None, REPNOTIFY_Always);
}

void UCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	//Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMathf::Clamp(NewValue, 0, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMathf::Clamp(NewValue, 0, GetMaxMana());
	}
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMathf::Clamp(NewValue, 0, GetMaxStamina());
	}
	if (Attribute == GetCharacterTimeDilationAttribute())
	{
		NewValue = FMathf::Clamp(NewValue, 0.0f, 1.0f);
	}
}

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		HealthChangedDelegate.Broadcast(GetHealth(), Data.EffectSpec.GetStackCount());
	}
	if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		MaxHealthChangedDelegate.Broadcast(GetMaxHealth(), Data.EffectSpec.GetStackCount());
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		ManaChangedDelegate.Broadcast(GetMana(), Data.EffectSpec.GetStackCount());
	}
	if (Data.EvaluatedData.Attribute == GetMaxManaAttribute())
	{
		MaxManaChangedDelegate.Broadcast(GetMaxMana(), Data.EffectSpec.GetStackCount());
	}
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		StaminaChangedDelegate.Broadcast(GetStamina(), Data.EffectSpec.GetStackCount());
	}
	if (Data.EvaluatedData.Attribute == GetMaxStaminaAttribute())
	{
		MaxStaminaChangedDelegate.Broadcast(GetMaxStamina(), Data.EffectSpec.GetStackCount());
	}
	if (Data.EvaluatedData.Attribute == GetBaseDamageAttribute())
	{
		BaseDamageChangedDelegate.Broadcast(GetBaseDamage(), Data.EffectSpec.GetStackCount());
	}
	if (Data.EvaluatedData.Attribute == GetCharacterTimeDilationAttribute())
	{
		CharacterTimeDilationChangedDelegate.Broadcast(GetCharacterTimeDilation(), Data.EffectSpec.GetStackCount());
	}
	if (Data.EvaluatedData.Attribute == GetCharacterLevelAttribute())
	{
		CharacterLevelChangedDelegate.Broadcast(GetCharacterLevel(), Data.EffectSpec.GetStackCount());
	}
}

