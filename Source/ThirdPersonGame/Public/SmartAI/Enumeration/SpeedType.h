#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Idle,
	Walk,
	Jog,
	Run,
	Sprint
};