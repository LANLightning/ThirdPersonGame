// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ToggleIsArmed.generated.h"

class ABaseEnemy;

UCLASS()
class THIRDPERSONGAME_API UBTTask_ToggleIsArmed : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Blackboard", meta=(AllowPrivateAccess="true"))
	bool IsArmed;

	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY()
	TObjectPtr<ABaseEnemy> EnemyCharacter;

	FTimerHandle TimerHandle;

	FTimerDelegate TimerDelegate;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnAnimationFinished() const;

public:
	UBTTask_ToggleIsArmed();
};
