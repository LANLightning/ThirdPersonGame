#pragma once

#include "GameplayTagContainer.h"

class FConst
{
public:
	inline static const FGameplayTag DeadTagConst = FGameplayTag::RequestGameplayTag(FName(TEXT("Character.State.Dead")));
	inline static const FGameplayTag StunTagConst = FGameplayTag::RequestGameplayTag(FName(TEXT("Character.State.Stun")));
	inline static const FGameplayTag EffectsRemovedOnDeadTagConst = FGameplayTag::RequestGameplayTag(FName(TEXT("Character.Effect.RemovedOnDread")));
	inline static const FGameplayTag AbilityTagConst = FGameplayTag::RequestGameplayTag(FName(TEXT("GameplayAbility")));
	inline static const FGameplayTag AbilityNotRemoveOnStunConst = FGameplayTag::RequestGameplayTag(FName(TEXT("GameplayAbility.NotRemoveOnStun")));
};
