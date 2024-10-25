#include "SmartAI/AI/BehaviorTreeTask/BTTask_SetSpeed.h"

#include "AIController.h"
#include "SmartAI/Interfaces/EnemyAI.h"

EBTNodeResult::Type UBTTask_SetSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	IEnemyAI* EnemyAI = Cast<IEnemyAI>(OwnerComp.GetAIOwner()->GetPawn());
	if (!EnemyAI)
	{
		return EBTNodeResult::Failed;
	}
	EnemyAI->SetSpeed(SpeedType);

	return EBTNodeResult::Succeeded;
}

UBTTask_SetSpeed::UBTTask_SetSpeed()
{
	bCreateNodeInstance = true;
	NodeName = TEXT("Set Speed");
}
