#include "AbilitySystem/Abilities/CharacterAbility.h"
#include "AbilitySystemComponent.h"
#include "Const.h"

UCharacterAbility::UCharacterAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ActivationBlockedTags.AddTag(FConst::DeadTagConst);
	ActivationBlockedTags.AddTag(FConst::StunTagConst);
}

void UCharacterAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (!ActivateOnGranted) return;
	ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
}
