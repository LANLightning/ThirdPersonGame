#include "SmartAI/Characters/Animation/BaseAnimInstance.h"

#include "Runtime/AnimGraphRuntime/Public/KismetAnimationLibrary.h"
#include "SmartAI/AI/Controller/Base/SmartAIEnemyControllerBase.h"
#include "SmartAI/Characters/Enemy/BaseEnemy.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ABaseEnemy>(TryGetPawnOwner());
}

void UBaseAnimInstance::PreUpdateAnimation(float DeltaSeconds)
{
	Super::PreUpdateAnimation(DeltaSeconds);

	if (!Character)
	{
		Character = Cast<ABaseEnemy>(TryGetPawnOwner());
	}
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Character || !Character->GetEnemyController()) return;
	MoveSpeed = Character->GetVelocity().Length();
	//HasAttackActor = Character->GetEnemyController()->GetAttackingTarget() != nullptr;
	//FocusMoveSpeed = Character->GetEnemyController()->GetMoveToDirection() * MoveSpeed;
	Direction = UKismetAnimationLibrary::CalculateDirection(Character->GetVelocity(), Character->GetActorRotation()); 
	IsWithinDefenseRange = Character->GetEnemyController()->IsWithinRangeToTarget(Character->GetDefenseRange());
	IsArmed = Character->GetIsArmed();
	IsResting = Character->GetIsResting();
}
