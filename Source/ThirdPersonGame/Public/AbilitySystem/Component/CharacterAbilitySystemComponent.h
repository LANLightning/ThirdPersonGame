// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CharacterAbilitySystemComponent.generated.h"

/**
 *
 */
class UCharacterAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FReceiveDamageDelegate, UCharacterAbilitySystemComponent*, float, float)

UCLASS()
class THIRDPERSONGAME_API UCharacterAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	//bool HasAbilityGiven;
	//bool HasStartupEffectsApplied;

public:
	FReceiveDamageDelegate ReceiveDamageDelegate;

	virtual void ReceiveDamage(UCharacterAbilitySystemComponent* AbilitySystemComponent, float RawDamage, float FinalDamage)
	{
		ReceiveDamageDelegate.Broadcast(AbilitySystemComponent, RawDamage, FinalDamage);
	}

	//bool GetAbilityGiven() const { return HasAbilityGiven; }

};
