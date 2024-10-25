#include "SmartAI/Components/ActionComponent.h"

#include "SmartAI/AI/Controller/Base/SmartAIEnemyControllerBase.h"
#include "SmartAI/Characters/BaseCharacter.h"

void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ABaseCharacter>(GetOwner());
	if(Character)
		EnemyController = Cast<ASmartAIEnemyControllerBase>(Character->GetController());
}
