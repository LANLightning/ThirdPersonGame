#include "SmartAI/AI/EQS/EnvQueryContext_PlayerStart.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void UEnvQueryContext_PlayerStart::ProvideContext(FEnvQueryInstance& QueryInstance,
												  FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	const APlayerStart* PlayerStart = Cast<APlayerStart>(
		UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));

	if (!PlayerStart) return;

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, PlayerStart);
}
