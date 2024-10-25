#include "SmartAI/AI/BehaviorTreeDecorator/BTDecorator_HealthCheck.h"

#include "SmartAI/Characters/Enemy/BaseEnemy.h"

UBTDecorator_HealthCheck::UBTDecorator_HealthCheck()
{
	bCreateNodeInstance = true;
	bNotifyTick = true;
	NodeName = TEXT("Check Health");
}

bool UBTDecorator_HealthCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (!OwnerComp.GetAIOwner()) return false;
	const ABaseEnemy* EnemyCharacter = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (!EnemyCharacter) return false;
	return  EnemyCharacter->GetHealthPercent() >= HealthThresholdPercentage;
}

void UBTDecorator_HealthCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	ConditionalFlowAbort(OwnerComp, EBTDecoratorAbortRequest::ConditionResultChanged);
}
