#pragma once

#include "CoreMinimal.h"
#include "SmartAI/Characters/BaseCharacter.h"
#include "SmartAIPlayerCharacter.generated.h"

enum class EFaction : uint8;
UCLASS()
class THIRDPERSONGAME_API ASmartAIPlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ASmartAIPlayerCharacter();
};
