#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_SetSpeed.generated.h"

enum class ESpeedType :uint8;

UCLASS()
class THIRDPERSONGAME_API UBTTask_SetSpeed : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Parameters", meta=(AllowPrivateAccess="true"))
	ESpeedType SpeedType;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UBTTask_SetSpeed();
};
