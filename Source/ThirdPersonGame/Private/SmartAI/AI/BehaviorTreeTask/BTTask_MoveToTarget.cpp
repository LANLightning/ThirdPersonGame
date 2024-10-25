#include "SmartAI/AI/BehaviorTreeTask/BTTask_MoveToTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "SmartAI/AI/Controller/Base/SmartAIEnemyControllerBase.h"

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName));

	if (!Target)
	{
		return EBTNodeResult::Failed;
	}

	const float AcceptableRange = Blackboard->GetValueAsFloat(AcceptableRangeKey.SelectedKeyName) - OffsetRange;

	EnemyController = Cast<ASmartAIEnemyControllerBase>(OwnerComp.GetAIOwner());

	if (!EnemyController || !Blackboard)
	{
		return EBTNodeResult::Failed;
	}

	AAIController* Controller = OwnerComp.GetAIOwner();
	if (!Controller)
	{
		return EBTNodeResult::Failed;
	}
	const EPathFollowingRequestResult::Type Result = Controller->MoveToActor(Target, AcceptableRange);

	switch (Result)
	{
	case EPathFollowingRequestResult::Failed:
		return EBTNodeResult::Failed;
	case EPathFollowingRequestResult::AlreadyAtGoal:
		return EBTNodeResult::Succeeded;
	case EPathFollowingRequestResult::RequestSuccessful:
		return EBTNodeResult::InProgress;
	default:
		return EBTNodeResult::Failed;
	}
}

void UBTTask_MoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	EnemyController = Cast<ASmartAIEnemyControllerBase>(OwnerComp.GetAIOwner());

	if (!EnemyController)
	{
		return;
	}

	switch (EnemyController->GetMoveStatus())
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

UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
	bCreateNodeInstance = true;
	bNotifyTick = true;
	NodeName = TEXT("Move To Target");
}
