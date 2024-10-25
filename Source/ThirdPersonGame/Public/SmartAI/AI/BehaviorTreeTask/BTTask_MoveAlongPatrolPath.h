#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_MoveAlongPatrolPath.generated.h"

UCLASS()
class THIRDPERSONGAME_API UBTTask_MoveAlongPatrolPath : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
public:
	UBTTask_MoveAlongPatrolPath();

};
