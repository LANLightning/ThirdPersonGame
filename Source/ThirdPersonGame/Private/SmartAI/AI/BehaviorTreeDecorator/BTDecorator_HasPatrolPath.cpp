#include "SmartAI/AI/BehaviorTreeDecorator/BTDecorator_HasPatrolPath.h"

#include "AIController.h"
#include "SmartAI/Interfaces/EnemyAI.h"
#include "SmartAI/AI/PathFinding/PatrolPath.h"

bool UBTDecorator_HasPatrolPath::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const IEnemyAI* EnemyAI = Cast<IEnemyAI>(OwnerComp.GetAIOwner()->GetPawn());

	if (!EnemyAI)
	{
		return false;
	}
	return EnemyAI->GetPatrolPath()->IsValidLowLevel();
}

UBTDecorator_HasPatrolPath::UBTDecorator_HasPatrolPath()
{
	bCreateNodeInstance = true;
	NodeName = TEXT("Has Patrol Path?");
}
