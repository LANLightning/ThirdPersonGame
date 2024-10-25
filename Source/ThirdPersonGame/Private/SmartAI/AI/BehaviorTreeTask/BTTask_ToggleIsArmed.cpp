#include "SmartAI/AI/BehaviorTreeTask/BTTask_ToggleIsArmed.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "SmartAI/Characters/Enemy/BaseEnemy.h"


EBTNodeResult::Type UBTTask_ToggleIsArmed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!EnemyCharacter)
	{
		EnemyCharacter = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
		if (!EnemyCharacter)
		{
			return EBTNodeResult::Failed;
		}
	}

	if(IsArmed == EnemyCharacter->GetIsArmed())
	{
		return EBTNodeResult::Succeeded;
	}

	const float AnimLength = EnemyCharacter->GetIsArmed() ? EnemyCharacter->UnEquipWeapon() : EnemyCharacter->EquipWeapon();

	if(AnimLength <= 0)
	{
		return EBTNodeResult::Succeeded;
	}

	BehaviorTreeComponent = &OwnerComp;
	TimerHandle.Invalidate();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, AnimLength, false);
	return EBTNodeResult::InProgress;
}

void UBTTask_ToggleIsArmed::OnAnimationFinished() const
{
	EnemyCharacter->SetIsArmed(IsArmed);
	FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Succeeded);
}

UBTTask_ToggleIsArmed::UBTTask_ToggleIsArmed()
{
	bCreateNodeInstance = true;
	bNotifyTick = true;
	NodeName = TEXT("Toggle Is Armed");

	TimerDelegate = FTimerDelegate::CreateUObject(this, &UBTTask_ToggleIsArmed::OnAnimationFinished);
}
