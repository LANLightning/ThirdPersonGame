// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CanSeeTarget.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONGAME_API UBTDecorator_CanSeeTarget : public UBTDecorator
{
	GENERATED_BODY()

public:

	UBTDecorator_CanSeeTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
