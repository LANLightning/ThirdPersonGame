// Fill out your copyright notice in the Description page of Project Settings.


#include "SmartAI/AI/BehaviorTreeTask/BTTask_FocusTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_FocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* FocusTarget = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

	if (!FocusTarget)
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetAIOwner()->SetFocus(FocusTarget);

	return EBTNodeResult::Succeeded;
}

UBTTask_FocusTarget::UBTTask_FocusTarget()
{
	bCreateNodeInstance = true;
	NodeName = TEXT("FocusTarget");
}
