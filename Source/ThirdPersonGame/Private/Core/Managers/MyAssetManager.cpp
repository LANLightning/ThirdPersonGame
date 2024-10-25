#include "Core/Managers/MyAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystem/Attributes/CharacterAttributeSet.h"

void UMyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
	UE_LOG(LogTemp, Warning, TEXT("[AssetManager] Succefully Initialized!"));
}
