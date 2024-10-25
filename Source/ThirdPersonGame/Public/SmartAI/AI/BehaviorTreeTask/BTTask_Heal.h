#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Heal.generated.h"

UCLASS()
class THIRDPERSONGAME_API UBTTask_Heal : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Parameters", meta=(AllowPrivateAccess="true"))
	float HealPercent;

public:
	UBTTask_Heal();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
