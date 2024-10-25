// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmartAI/AI/Controller/Base/SmartAIEnemyControllerBase.h"
#include "SmartAI/AI/PathFinding/PatrolPath.h"
#include "SmartAI/Characters/BaseCharacter.h"
#include "SmartAI/Interfaces/EnemyAI.h"
#include "BaseEnemy.generated.h"

class UWidgetComponent;
class UActionComponent;

UCLASS()
class THIRDPERSONGAME_API ABaseEnemy : public ABaseCharacter, public IEnemyAI
{
	GENERATED_BODY()

	TObjectPtr<UBaseAnimInstance> EnemyAnimInstance;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UWidgetComponent> FloatingHealthBarComponent;

	UPROPERTY()
	TObjectPtr<ASmartAIEnemyControllerBase> EnemyController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UActionComponent> ActionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PathFinding", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<APatrolPath> PatrolPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions|Speed", meta = (AllowPrivateAccess = "true"))
	float WaleSpeed = 150;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions|Speed", meta = (AllowPrivateAccess = "true"))
	float JogSpeed = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions|Speed", meta = (AllowPrivateAccess = "true"))
	float RunSpeed = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ArmAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> DisArmAnimMontage;
public:
	ABaseEnemy();

	void Heal(AActor* Healer, const float HealAmount);
	virtual void SetSpeed(ESpeedType InSpeedType) override;
	virtual float GetHealthPercent() const override;

	FORCEINLINE virtual APatrolPath* GetPatrolPath() const override;

	FORCEINLINE virtual float EquipWeapon() override;

	FORCEINLINE virtual float UnEquipWeapon() override;

	FORCEINLINE TObjectPtr<UActionComponent> GetAction() const { return ActionComponent; }
	FORCEINLINE TObjectPtr<UBaseAnimInstance> GetAnimInstance() const { return EnemyAnimInstance; }
	FORCEINLINE TObjectPtr<ASmartAIEnemyControllerBase> GetEnemyController() const { return EnemyController; }
	FORCEINLINE bool GetIsArmed() const { return IsArmed; }
	FORCEINLINE void SetIsArmed(const bool InValue) { IsArmed = InValue; }
	FORCEINLINE float GetAttackRange() const { return AttackRange; }
	FORCEINLINE float GetDefenseRange() const { return DefenseRange; }
	FORCEINLINE void SetIsResting(const bool InValue) { IsResting = InValue; }
	FORCEINLINE bool GetIsResting() const { return IsResting; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions|Attack", meta = (AllowPrivateAccess = "true"))
	float AttackRange = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions|Attack", meta = (AllowPrivateAccess = "true"))
	float DefenseRange = 350;

	virtual void BeginPlay() override;

	bool IsAttacking;
	UPROPERTY(EditDefaultsOnly, Category = "Status")
	bool IsArmed = false;
	UPROPERTY(EditDefaultsOnly, Category = "Status")
	bool IsResting;

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

};
