// Fill out your copyright notice in the Description page of Project Settings.


#include "SmartAI/AI/BehaviorTreeTask/BTTask_ClearFocus.h"

#include "AIController.h"

EBTNodeResult::Type UBTTask_ClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}
	OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::LastFocusPriority);

	

	return EBTNodeResult::Succeeded;
}

UBTTask_ClearFocus::UBTTask_ClearFocus()
{
	bCreateNodeInstance = true;
	NodeName = TEXT("ClearFocus");
}
