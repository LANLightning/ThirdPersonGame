#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"

class ASmartAIEnemyControllerBase;
class ABaseCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THIRDPERSONGAME_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

	//UPROPERTY(BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	TObjectPtr<ABaseCharacter> Character;

	//UPROPERTY(BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASmartAIEnemyControllerBase> EnemyController;

protected:
	virtual void BeginPlay() override;

};
