#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAISenseType : uint8
{
	None,
	Sight,
	Hearing,
	Damage,
};
