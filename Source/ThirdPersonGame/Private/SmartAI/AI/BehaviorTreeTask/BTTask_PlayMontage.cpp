#include "SmartAI/AI/BehaviorTreeTask/BTTask_PlayMontage.h"

#include "AIController.h"
#include "SmartAI/Characters/BaseCharacter.h"

void UBTTask_PlayMontage::OnMontageFinishedPlaying() const
{
	FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Succeeded);
}

EBTNodeResult::Type UBTTask_PlayMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!MontageToPlay)
	{
		return EBTNodeResult::Succeeded;
	}

	if(!Character)
	{
		Character = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
		if (!Character)
		{
			return EBTNodeResult::Failed;
		}
	}

	Character->PlayAnimMontage(MontageToPlay);
	const float MontageTime = MontageToPlay->GetPlayLength() / MontageToPlay->RateScale;

	if (MontageTime <= 0)
	{
		return EBTNodeResult::Succeeded;
	}

	BehaviorTreeComponent = &OwnerComp;
	TimerHandle.Invalidate();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, MontageTime, false);

	return EBTNodeResult::InProgress;
}

UBTTask_PlayMontage::UBTTask_PlayMontage()
{
	bCreateNodeInstance = true;
	NodeName = TEXT("Play Montage");
	TimerDelegate = FTimerDelegate::CreateUObject(this, &UBTTask_PlayMontage::OnMontageFinishedPlaying);
}
