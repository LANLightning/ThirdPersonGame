// Fill out your copyright notice in the Description page of Project Settings.


#include "SmartAI/AI/BehaviorTreeDecorator/BTDecorator_IsArmed.h"

#include "AIController.h"
#include "SmartAI/Characters/Enemy/BaseEnemy.h"

bool UBTDecorator_IsArmed::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ABaseEnemy* Character = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if (!Character) return false;

	return Character->GetIsArmed();
}

void UBTDecorator_IsArmed::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ConditionalFlowAbort(OwnerComp, EBTDecoratorAbortRequest::ConditionResultChanged);
}

UBTDecorator_IsArmed::UBTDecorator_IsArmed()
{
	bNotifyTick = true;
	bCreateNodeInstance = true;
	NodeName = TEXT("Is Armed?");
}
