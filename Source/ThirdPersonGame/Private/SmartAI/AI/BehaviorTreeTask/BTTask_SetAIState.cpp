#include "SmartAI/AI/BehaviorTreeTask/BTTask_SetAIState.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "SmartAI/AI/Controller/Base/SmartAIEnemyControllerBase.h"
#include "SmartAI/Enumeration/AIStateType.h"

EBTNodeResult::Type UBTTask_SetAIState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const ASmartAIEnemyControllerBase* EnemyController = Cast<ASmartAIEnemyControllerBase>(OwnerComp.GetAIOwner());
	if (!EnemyController)
	{
		return EBTNodeResult::Failed;
	}

	switch (TargetState)
	{
	case EAIStateType::Idle:
		EnemyController->SetPassiveState();
		break;
	case EAIStateType::Combat:
		break;
	case EAIStateType::Investigating:
		break;
	case EAIStateType::Resting:
		EnemyController->SetRestingState();
		break;
	case EAIStateType::Stun:
		break;
	case EAIStateType::Dead:
		break;
	default: ;
	}

	EnemyController->SetStateBlackboardKey(TargetState);
	return EBTNodeResult::Succeeded;
}

UBTTask_SetAIState::UBTTask_SetAIState()
{
	bCreateNodeInstance = true;
	NodeName = TEXT("Set AI State");
}
