#include "SmartAI/Characters/Enemy/BaseEnemy.h"

#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SmartAI/AI/Controller/Base/SmartAIEnemyControllerBase.h"
#include "SmartAI/Characters/Animation/BaseAnimInstance.h"
#include "SmartAI/Components/ActionComponent.h"
#include "SmartAI/Components/HealthComponent.h"
#include "SmartAI/Enumeration/SpeedType.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "SmartAI/Enumeration/Faction.h"
#include "SmartAI/UI/HealthBarWidget.h"

ABaseEnemy::ABaseEnemy()
{
	ActionComponent = CreateDefaultSubobject<UActionComponent>(TEXT("Action"));
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	bUseControllerRotationYaw = false;

	Faction = EFaction::Enemy;

	FloatingHealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Floating Health Bar"));
	FloatingHealthBarComponent->SetupAttachment(GetRootComponent());
	FloatingHealthBarComponent->SetRelativeLocation(FVector(0, 0, 120));
	FloatingHealthBarComponent->SetDrawAtDesiredSize(true);

	const TCHAR* Path = TEXT("/Game/UI/WBP_FloatingHealthBar");
	static ConstructorHelpers::FClassFinder<UHealthBarWidget> HealthBarWidgetClassFinder(Path);

	if (HealthBarWidgetClassFinder.Succeeded())
	{
		FloatingHealthBarComponent->SetWidgetClass(HealthBarWidgetClassFinder.Class);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can Not Find [HealthBarWidgetClass] At [%s]"), Path)
	}
}

APatrolPath* ABaseEnemy::GetPatrolPath() const
{
	return PatrolPath.Get();
}

void ABaseEnemy::SetSpeed(const ESpeedType InSpeedType)
{
	float Speed = 0;
	switch (InSpeedType)
	{
	case ESpeedType::Idle:
		break;
	case ESpeedType::Walk:
		Speed = WaleSpeed;
		break;
	case ESpeedType::Jog:
		Speed = JogSpeed;
		break;
	case ESpeedType::Run:
		Speed = RunSpeed;
		break;
	case ESpeedType::Sprint:
		break;
	default:;
	}
	GetCharacterMovement()->MaxWalkSpeed = Speed;

}

float ABaseEnemy::GetHealthPercent() const
{
	return GetHealth()->GetHealthPercent();
}

void ABaseEnemy::Heal(AActor* Healer, const float HealAmount)
{
	HealHealth(Healer, HealAmount);
}

float ABaseEnemy::EquipWeapon()
{
	if (ArmAnimMontage)
	{
		return PlayAnimMontage(ArmAnimMontage) / ArmAnimMontage->RateScale;
	}
	return 0.0f;
	//FTimerHandle TimerHandle;
	//GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseEnemy::OnFinishArmed, AnimLength);
}

float ABaseEnemy::UnEquipWeapon()
{
	if (ArmAnimMontage)
	{
		return PlayAnimMontage(DisArmAnimMontage) / DisArmAnimMontage->RateScale;
	}
	return 0.0f;

	//FTimerHandle TimerHandle;
	//GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseEnemy::OnFinishDisArmed, AnimLength);
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyAnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
	EnemyController = Cast<ASmartAIEnemyControllerBase>(GetController());

	HealthComponent->InitializeHealth();
	UHealthBarWidget* HealthBarWidget = Cast<UHealthBarWidget>(FloatingHealthBarComponent->GetWidget());
	if (!HealthBarWidget) return;
	HealthBarWidget->SetUp(HealthComponent);
}

ETeamAttitude::Type ABaseEnemy::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamActor = Cast<IGenericTeamAgentInterface>(&Other);

	if (!OtherTeamActor)
	{
		return ETeamAttitude::Type::Neutral;
	}

	switch (OtherTeamActor->GetGenericTeamId())
	{
	case static_cast<uint8>(EFaction::Enemy):
		return ETeamAttitude::Type::Friendly;
	case static_cast<uint8>(EFaction::Player):
		return ETeamAttitude::Type::Hostile;
	case static_cast<uint8>(EFaction::NoFaction):
		return ETeamAttitude::Type::Neutral;
	default:
		return ETeamAttitude::Type::Neutral;
	}
}

void ABaseEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
