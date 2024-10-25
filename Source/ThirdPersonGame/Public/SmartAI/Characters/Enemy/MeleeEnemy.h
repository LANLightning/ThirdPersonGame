#pragma once

#include "CoreMinimal.h"
#include "SmartAI/Characters/Enemy/BaseEnemy.h"
#include "MeleeEnemy.generated.h"

UCLASS()
class THIRDPERSONGAME_API AMeleeEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	AMeleeEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
};
