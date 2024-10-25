#include "SmartAI/AI/BehaviorTreeTask/BTTask_MoveAlongPatrolPath.h"

#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "SmartAI/AI/PathFinding/PatrolPath.h"
#include "SmartAI/Interfaces/EnemyAI.h"

EBTNodeResult::Type UBTTask_MoveAlongPatrolPath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!OwnerPawn)
	{
		return EBTNodeResult::Failed;
	}

	if (const IEnemyAI* Enemy = Cast<IEnemyAI>(OwnerPawn))
	{
		APatrolPath* PatrolPath = Enemy->GetPatrolPath();

		if(!PatrolPath)
		{
			return EBTNodeResult::Failed;
		}

		EPathFollowingRequestResult::Type Result = OwnerComp.GetAIOwner()->MoveToLocation(PatrolPath->GetWaypoint());

		switch (Result)
		{
		case EPathFollowingRequestResult::Failed:
			return EBTNodeResult::Failed;
		case EPathFollowingRequestResult::AlreadyAtGoal:
			PatrolPath->UpdateWaypoint();
			return EBTNodeResult::Succeeded;
		case EPathFollowingRequestResult::RequestSuccessful:
			return EBTNodeResult::InProgress;
		default:;
		}

		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}

void UBTTask_MoveAlongPatrolPath::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetAIOwner())
	{
		switch (OwnerComp.GetAIOwner()->GetMoveStatus())
		{
		case EPathFollowingStatus::Idle:
		case EPathFollowingStatus::Waiting:
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			break;
		case EPathFollowingStatus::Paused:
		case EPathFollowingStatus::Moving:
			break;
		default:;
		}
	}
}

UBTTask_MoveAlongPatrolPath::UBTTask_MoveAlongPatrolPath()
{
	bNotifyTick = true;
	bCreateNodeInstance = true;
	NodeName = TEXT("Move Along Patrol Path");
}
