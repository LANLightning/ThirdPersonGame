#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CharacterAbility.generated.h"

enum class ECharacterAbilityID : uint8;
enum class ECharacterAbilityInputID : uint8;

UCLASS()
class THIRDPERSONGAME_API UCharacterAbility : public UGameplayAbility
{
	GENERATED_BODY()

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
	TEnumAsByte<EGameplayAbilityInstancingPolicy::Type> DefaultInstancedPolicy;*/

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Params", meta = (AllowPrivateAccess = "true"))
	//ECharacterAbilityID AbilityID;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Params", meta = (AllowPrivateAccess = "true"))
	//ECharacterAbilityInputID AbilityInputID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params", meta = (AllowPrivateAccess = "true"))
	bool ActivateOnGranted;

public:
	UCharacterAbility();

	//ECharacterAbilityID GetAbilityID() const { return AbilityID; }
	//uint8 GetAbilityInputID() const { return static_cast<uint8>(AbilityInputID); }

	bool GetActivateOnGranted() const { return ActivateOnGranted; }

	//void SetActivateOnGranted(const bool InValue) { ActivateOnGranted = InValue; }

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
