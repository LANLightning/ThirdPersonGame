#include "SmartAI/AI/BehaviorTreeTask/BTTask_Heal.h"

#include "AIController.h"
#include "SmartAI/Characters/Enemy/BaseEnemy.h"
#include "SmartAI/Components/HealthComponent.h"

UBTTask_Heal::UBTTask_Heal()
{
	bCreateNodeInstance = true;
	NodeName = TEXT("Heal");

}

EBTNodeResult::Type UBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	ABaseEnemy* EnemyCharacter = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (!EnemyCharacter || !EnemyCharacter->GetHealth()) return EBTNodeResult::Failed;
	EnemyCharacter->Heal(EnemyCharacter, EnemyCharacter->GetHealth()->GetMaxHealth() * HealPercent);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
