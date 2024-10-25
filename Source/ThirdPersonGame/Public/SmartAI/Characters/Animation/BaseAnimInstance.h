// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

class ABaseEnemy;
class ASmartAIEnemyControllerBase;

UCLASS()
class THIRDPERSONGAME_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<ABaseEnemy> Character;

protected:
	virtual void NativeInitializeAnimation() override;

	virtual void PreUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, Category = "Animation Parameters")
	float MoveSpeed;
		
	//UPROPERTY(BlueprintReadOnly, Category = "Animation Parameters")
	//bool HasAttackActor;

	UPROPERTY(BlueprintReadOnly, Category = "Animation Parameters")
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = "Animation Parameters")
	bool IsWithinDefenseRange;

	UPROPERTY(BlueprintReadOnly, Category = "Animation Parameters")
	bool IsArmed;
	
	UPROPERTY(BlueprintReadOnly, Category = "Animation Parameters")
	bool IsResting;
};
