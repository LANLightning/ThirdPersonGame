#include "SmartAI/Characters/Enemy/MeleeEnemy.h"

AMeleeEnemy::AMeleeEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMeleeEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AMeleeEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
