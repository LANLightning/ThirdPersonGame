#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SmartAIEnemyControllerBase.generated.h"

class ABaseEnemy;
enum class EAISenseType : uint8;
class UAISenseConfig_Sight;
enum class EAIStateType : uint8;

UCLASS()
class THIRDPERSONGAME_API ASmartAIEnemyControllerBase : public AAIController
{
	GENERATED_BODY()

	TObjectPtr<ABaseEnemy> EnemyCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditAnywhere, Category="Behavior Tree", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "Behavior Tree", meta = (AllowPrivateAccess = "true"))
	EAIStateType InitialState;

	UPROPERTY(EditAnywhere, Category = "Blackboard|Keys", meta = (AllowPrivateAccess = "true"))
	FName AttackTargetName = FName(TEXT("AttackTarget"));

	UPROPERTY(EditAnywhere, Category = "Blackboard|Keys", meta = (AllowPrivateAccess = "true"))
	FName StateKeyName = FName(TEXT("State"));

	UPROPERTY(EditAnywhere, Category = "Blackboard|Keys", meta = (AllowPrivateAccess = "true"))
	FName DestinationKeyName = FName(TEXT("Destination"));

	UPROPERTY(EditAnywhere, Category = "Blackboard|Keys", meta = (AllowPrivateAccess = "true"))
	FName AttackRangeKeyName = FName(TEXT("AttackRange"));

	UPROPERTY(EditAnywhere, Category = "Blackboard|Keys", meta = (AllowPrivateAccess = "true"))
	FName DefenseRangeKeyName = FName(TEXT("DefenseRange"));

	FVector LastStimulusLocation;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AActor* AttackingTarget;

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& Actors);

	UFUNCTION()
	void OnForgottenTarget(AActor* Actor);

	void OnTargetSighted(AActor* TargetActor);

	void InvestigateSound(const FVector& SoundLocation);

	void FightBack(AActor* Actor);

	EAIStateType GetCurrentState() const;

public:
	ASmartAIEnemyControllerBase();

	void SetStateBlackboardKey(const EAIStateType InState) const;

	void SetCombatState(AActor* TargetActor);

	void SetRestingState() const;

	void SetPassiveState() const;

	void SetInvestigatingState(const FVector& Destination) const;

	//virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	bool HasDetectedActor(AActor* ActorToDetected, EAISenseType SenseType);

	//float GetDistanceToTarget() const;

	bool IsWithinRangeToTarget(const float Range) const;

	//FVector GetMoveToDirection() const;

	//FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(static_cast<uint8>(Faction)); }
	//FORCEINLINE bool GetIsFocusing() const { return GetFocusActor() != nullptr; }
	FORCEINLINE AActor* GetAttackingTarget() const{ return AttackingTarget; }

	FORCEINLINE void ClearAttackingTarget() { AttackingTarget = nullptr; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
};
