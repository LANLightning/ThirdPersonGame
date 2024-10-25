#include "SmartAI/Animations/AnimNotifies/AnimNotify_OnToggleArmed.h"

#include "SmartAI/Characters/Enemy/RangedEnemy.h"

FString UAnimNotify_OnToggleArmed::GetNotifyName_Implementation() const
{
	return TEXT("Toggle Armed");
}

void UAnimNotify_OnToggleArmed::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp->GetOwner()) return;

	ARangedEnemy* RangedEnemy = Cast<ARangedEnemy>(MeshComp->GetOwner());

	if (!RangedEnemy) return;

	RangedEnemy->ToggleArmed();

}
