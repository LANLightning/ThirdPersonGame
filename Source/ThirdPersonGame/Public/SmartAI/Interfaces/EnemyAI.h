#pragma once

#include "CoreMinimal.h"
#include "SmartAI/AI/PathFinding/PatrolPath.h"
#include "UObject/Interface.h"
#include "EnemyAI.generated.h"

enum class ESpeedType : uint8;

UINTERFACE(MinimalAPI)
class UEnemyAI : public UInterface
{
	GENERATED_BODY()
};

class THIRDPERSONGAME_API IEnemyAI
{
	GENERATED_BODY()
		
public:

	virtual APatrolPath* GetPatrolPath() const = 0;

	virtual void SetSpeed(ESpeedType InSpeedType) = 0;

	virtual float EquipWeapon() = 0;

	virtual float UnEquipWeapon() = 0;

	virtual float GetHealthPercent() const = 0;
};
