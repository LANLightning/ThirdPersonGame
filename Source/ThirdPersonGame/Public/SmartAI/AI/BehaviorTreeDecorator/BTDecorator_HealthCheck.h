#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_HealthCheck.generated.h"

UCLASS()
class THIRDPERSONGAME_API UBTDecorator_HealthCheck : public UBTDecorator
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Parameters", meta=(AloowPrivateAccess="true", UIMin="0", UIMax="1"))
	float HealthThresholdPercentage = 0.25f;

public:
	UBTDecorator_HealthCheck();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
