#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "DefaultPlayerState.generated.h"

UCLASS()
class THIRDPERSONGAME_API ADefaultPlayerState : public APlayerState//, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ADefaultPlayerState();

#if WITH_EDITOR
	UFUNCTION(BlueprintCallable)
	void ShowAbilityCancelConfirmText(const bool ShouldShow) {}
#endif
};
