#include "SmartAI/AI/Controller/Base/SmartAIEnemyControllerBase.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "SmartAI/Characters/Enemy/BaseEnemy.h"
#include "SmartAI/Enumeration/AIStateType.h"
#include "SmartAI/Enumeration/AISenseType.h"
#include "UObject/ConstructorHelpers.h"

ASmartAIEnemyControllerBase::ASmartAIEnemyControllerBase()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeFinder(TEXT("/Game/SmartAi/Character/Enemy/BT_Enemy_Base"));

	if (BehaviorTreeFinder.Succeeded())
	{
		BehaviorTree = BehaviorTreeFinder.Object;
	}
	check(BehaviorTree);
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	const TObjectPtr<UAISenseConfig_Sight> SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	const TObjectPtr<UAISenseConfig_Hearing> HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	const TObjectPtr<UAISenseConfig_Damage> DamageSenseConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageSenseConfig"));

	SightConfig->SightRadius = 800;
	SightConfig->LoseSightRadius = 1200;
	SightConfig->PeripheralVisionAngleDegrees = 60;
	SightConfig->SetMaxAge(5);

	HearingConfig->HearingRange = 500;
	HearingConfig->SetMaxAge(3);

	DamageSenseConfig->SetMaxAge(5);

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->ConfigureSense(*HearingConfig);
	AIPerceptionComponent->ConfigureSense(*DamageSenseConfig);
	AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
}

void ASmartAIEnemyControllerBase::SetStateBlackboardKey(const EAIStateType InState) const
{
	Blackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(InState));
}

void ASmartAIEnemyControllerBase::SetCombatState(AActor* TargetActor)
{
	if (EnemyCharacter->GetTeamAttitudeTowards(*TargetActor) != ETeamAttitude::Type::Hostile) return;

	AttackingTarget = TargetActor;
	Blackboard->SetValueAsObject(AttackTargetName, TargetActor);
	EnemyCharacter->SetIsResting(false);
	SetStateBlackboardKey(EAIStateType::Combat);
}

void ASmartAIEnemyControllerBase::SetRestingState() const
{
	EnemyCharacter->SetIsResting(true);
	SetStateBlackboardKey(EAIStateType::Resting);
}

void ASmartAIEnemyControllerBase::SetPassiveState() const
{
	EnemyCharacter->SetIsResting(false);
	SetStateBlackboardKey(EAIStateType::Idle);
}

void ASmartAIEnemyControllerBase::SetInvestigatingState(const FVector& Destination) const
{
	Blackboard->SetValueAsVector(DestinationKeyName, Destination);
	EnemyCharacter->SetIsResting(false);
	SetStateBlackboardKey(EAIStateType::Investigating);
}

bool ASmartAIEnemyControllerBase::HasDetectedActor(AActor* ActorToDetected, EAISenseType SenseType)
{
	TSubclassOf<UAISense> SenseClass;
	FActorPerceptionBlueprintInfo OutPerceptionInfo;
	PerceptionComponent->GetActorsPerception(ActorToDetected, OutPerceptionInfo);

	for (FAIStimulus Stimulus: OutPerceptionInfo.LastSensedStimuli)
	{
		switch (SenseType)
		{
		case EAISenseType::None:
			break;
		case EAISenseType::Sight:
			SenseClass = UAISense_Sight::StaticClass();
			break;
		case EAISenseType::Hearing:
			SenseClass = UAISense_Hearing::StaticClass();
			break;
		case EAISenseType::Damage:
			SenseClass = UAISense_Damage::StaticClass();
			break;
		default:;
		}

		if(SenseClass == UAIPerceptionSystem::GetSenseClassForStimulus(this, Stimulus) && Stimulus.WasSuccessfullySensed())
		{
			LastStimulusLocation = Stimulus.StimulusLocation;
			return true;
		}
	}

	return false;
}

//float ASmartAIEnemyControllerBase::GetDistanceToTarget() const
//{
//	if (!EnemyCharacter || !AttackingTarget) 
//		return 0;
//	return EnemyCharacter->GetDistanceTo(AttackingTarget);
//}

bool ASmartAIEnemyControllerBase::IsWithinRangeToTarget(const float Range) const
{
	if (!EnemyCharacter || !AttackingTarget)
	{
		return false;
	}

	return EnemyCharacter->GetDistanceTo(AttackingTarget) < Range;
}

void ASmartAIEnemyControllerBase::OnPerceptionUpdated(const TArray<AActor*>& Actors)
{
	for (AActor* Actor : Actors)
	{
		if (HasDetectedActor(Actor, EAISenseType::Sight))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, TEXT("Sight Sense Detected Target!"));
			OnTargetSighted(Actor);
		}
		if (HasDetectedActor(Actor, EAISenseType::Hearing))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, TEXT("Hearing Sense Detected Target!"));
			InvestigateSound(LastStimulusLocation);
		}
		if (HasDetectedActor(Actor, EAISenseType::Damage))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Damage Sense Detected Target!"));
			FightBack(Actor);
		}
	}
}

void ASmartAIEnemyControllerBase::OnForgottenTarget(AActor* Actor)
{
	if(Actor == AttackingTarget)
	{
		AttackingTarget = nullptr;
		if (GetCurrentState() == EAIStateType::Resting) return;
		SetInvestigatingState(Actor->GetActorLocation());
	}
}

void ASmartAIEnemyControllerBase::OnTargetSighted(AActor* TargetActor)
{
	switch (GetCurrentState()) {
	case EAIStateType::Idle:
		SetCombatState(TargetActor);
		break;
	case EAIStateType::Combat:
		break;
	case EAIStateType::Investigating:
		SetCombatState(TargetActor);
		break;
	case EAIStateType::Resting:
		SetCombatState(TargetActor);
		break;
	case EAIStateType::Stun:
		break;
	case EAIStateType::Dead:
		break;

	default:;
	}
}

void ASmartAIEnemyControllerBase::InvestigateSound(const FVector& SoundLocation)
{
	switch (GetCurrentState())
	{
	case EAIStateType::Idle:
		SetInvestigatingState(SoundLocation);
		break;
	case EAIStateType::Combat:
		break;
	case EAIStateType::Investigating:
		SetInvestigatingState(SoundLocation);
		break;
	case EAIStateType::Resting:
		SetInvestigatingState(SoundLocation);
		break;
	case EAIStateType::Stun:
		break;
	case EAIStateType::Dead:
		break;
	}
}

void ASmartAIEnemyControllerBase::FightBack(AActor* Actor)
{
	switch (GetCurrentState())
	{
	case EAIStateType::Idle:
		SetCombatState(Actor);
		break;
	case EAIStateType::Combat:
		break;
	case EAIStateType::Investigating:
		SetCombatState(Actor);
		break;
	case EAIStateType::Resting:
		SetCombatState(Actor);
		break;
	case EAIStateType::Stun:
		break;
	case EAIStateType::Dead:
		break;
	}
}

EAIStateType ASmartAIEnemyControllerBase::GetCurrentState() const
{
	return static_cast<EAIStateType>(Blackboard->GetValueAsEnum(StateKeyName));
}

//FVector ASmartAIEnemyControllerBase::GetMoveToDirection() const
//{
//	const FVector Destination = Blackboard->GetValueAsVector(DestinationKeyName);
//
//	return (Destination - GetPawn()->GetActorLocation()).GetSafeNormal();
//}

void ASmartAIEnemyControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	EnemyCharacter = Cast<ABaseEnemy>(InPawn);

	if (!BehaviorTree) return;
	RunBehaviorTree(BehaviorTree);
}

void ASmartAIEnemyControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (EnemyCharacter)
	{
		Blackboard->SetValueAsFloat(AttackRangeKeyName, EnemyCharacter->GetAttackRange());
		Blackboard->SetValueAsFloat(DefenseRangeKeyName, EnemyCharacter->GetDefenseRange());
	}
	SetStateBlackboardKey(InitialState);

	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ASmartAIEnemyControllerBase::OnPerceptionUpdated);
	AIPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &ASmartAIEnemyControllerBase::OnForgottenTarget);
}
