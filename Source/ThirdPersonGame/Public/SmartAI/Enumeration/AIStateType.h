#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAIStateType : uint8
{
	Idle,
	Combat,
	Investigating,
	Resting,
	Stun,
	Dead
};
