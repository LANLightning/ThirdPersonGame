#include "SmartAI/AI/BehaviorTreeDecorator/BTDecorator_IsInIdealRangeToTarget.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "SmartAI/AI/Controller/Base/SmartAIEnemyControllerBase.h"

bool UBTDecorator_IsInIdealRangeToTarget::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const ASmartAIEnemyControllerBase* EnemyController = Cast<ASmartAIEnemyControllerBase>(OwnerComp.GetAIOwner());
	if (!EnemyController)
	{
		return false;
	}

	const float Range = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());
	return EnemyController->IsWithinRangeToTarget(Range);
}

void UBTDecorator_IsInIdealRangeToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ConditionalFlowAbort(OwnerComp, EBTDecoratorAbortRequest::ConditionResultChanged);
}

UBTDecorator_IsInIdealRangeToTarget::UBTDecorator_IsInIdealRangeToTarget()
{
	bNotifyTick = true;
	bCreateNodeInstance = true;
	NodeName = TEXT("Is In Ideal Range");
}
