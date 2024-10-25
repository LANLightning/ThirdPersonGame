// Fill out your copyright notice in the Description page of Project Settings.


#include "SmartAI/Animations/AnimNotifies/AnimNotify_Fire.h"

#include "SmartAI/Characters/Enemy/RangedEnemy.h"

FString UAnimNotify_Fire::GetNotifyName_Implementation() const
{
	return TEXT("Fire");
}

void UAnimNotify_Fire::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp->GetOwner()) return;

	ARangedEnemy* RangedEnemy = Cast<ARangedEnemy>(MeshComp->GetOwner());

	if (!RangedEnemy) return;

	RangedEnemy->Fire();
}

