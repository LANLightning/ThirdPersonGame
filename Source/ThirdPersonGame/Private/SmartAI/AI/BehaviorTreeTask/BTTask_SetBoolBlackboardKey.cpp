#include "SmartAI/AI/BehaviorTreeTask/BTTask_SetBoolBlackboardKey.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_SetBoolBlackboardKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	if (!Blackboard)
	{
		return EBTNodeResult::Failed;
	}
	Blackboard->SetValueAsBool(GetSelectedBlackboardKey(), KeyValueTrueOrFalse);

	return EBTNodeResult::Succeeded;
}

UBTTask_SetBoolBlackboardKey::UBTTask_SetBoolBlackboardKey()
{
	bCreateNodeInstance = true;
	NodeName = TEXT("Set Bool Blackboard Key");
}
