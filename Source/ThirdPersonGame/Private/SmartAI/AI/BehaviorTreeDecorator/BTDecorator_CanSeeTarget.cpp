// Fill out your copyright notice in the Description page of Project Settings.


#include "SmartAI/AI/BehaviorTreeDecorator/BTDecorator_CanSeeTarget.h"

#include "AIController.h"
#include "SmartAI/Characters/Enemy/RangedEnemy.h"

UBTDecorator_CanSeeTarget::UBTDecorator_CanSeeTarget()
{
	bNotifyTick = true;
	bCreateNodeInstance = true;
	NodeName = TEXT("Can See Target");
}

void UBTDecorator_CanSeeTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ConditionalFlowAbort(OwnerComp, EBTDecoratorAbortRequest::ConditionResultChanged);
}

bool UBTDecorator_CanSeeTarget::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (!OwnerComp.GetAIOwner() || !OwnerComp.GetAIOwner()->GetPawn()) return false;

	const ARangedEnemy* RangedEnemy = Cast<ARangedEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if (!RangedEnemy)
	{
		return false;
	}

	return RangedEnemy->LineTraceTarget();
}
