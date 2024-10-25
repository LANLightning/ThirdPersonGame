#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_PlayMontage.generated.h"

class ABaseCharacter;

UCLASS()
class THIRDPERSONGAME_API UBTTask_PlayMontage : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Animation", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UAnimMontage> MontageToPlay;

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY()
	TObjectPtr<ABaseCharacter> Character;

	FTimerDelegate TimerDelegate;

	FTimerHandle TimerHandle;

	void OnMontageFinishedPlaying() const;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UBTTask_PlayMontage();
};
