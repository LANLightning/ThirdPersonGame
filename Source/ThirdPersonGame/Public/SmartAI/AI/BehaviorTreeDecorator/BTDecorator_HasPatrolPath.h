#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlueprintBase.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTDecorator_HasPatrolPath.generated.h"

UCLASS()
class THIRDPERSONGAME_API UBTDecorator_HasPatrolPath : public UBTDecorator_BlueprintBase
{
	GENERATED_BODY()

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:
	UBTDecorator_HasPatrolPath();
};
