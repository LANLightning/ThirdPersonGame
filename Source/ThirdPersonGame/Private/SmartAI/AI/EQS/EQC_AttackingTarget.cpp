#include "SmartAI/AI/EQS/EQC_AttackingTarget.h"

#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "SmartAI/Characters/Enemy/BaseEnemy.h"

void UEQC_AttackingTarget::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	//Super::ProvideContext(QueryInstance, ContextData);

	//APlayerStart* PlayerStart;

	//PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));

	//UEnvQueryItemType_Actor::SetContextHelper(ContextData, PlayerStart);

	Super::ProvideContext(QueryInstance, ContextData);

	const ABaseEnemy* Querier = Cast<ABaseEnemy>(QueryInstance.Owner.Get());

	if (!Querier || !Querier->GetEnemyController()) return;

	const AActor* ResultingActor = Querier->GetEnemyController()->GetAttackingTarget();

	if (!ResultingActor) return;

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, ResultingActor);


}
