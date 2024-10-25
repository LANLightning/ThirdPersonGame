#include "SmartAI/AI/PathFinding/PatrolPath.h"

#include "Components/SplineComponent.h"

void APatrolPath::BeginPlay()
{
	Super::BeginPlay();
}

APatrolPath::APatrolPath()
{
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Route"));
	SplineComponent->SetupAttachment(Root);
}

void APatrolPath::UpdateWaypoint()
{
	CurrentWaypointIndex += Direction;
	if (CurrentWaypointIndex == SplineComponent->GetNumberOfSplinePoints() - 1)
	{
		Direction = -1;
	}
	if (CurrentWaypointIndex == 0)
	{
		Direction = 1;
	}
}

FVector APatrolPath::GetWaypoint() const
{
	return SplineComponent->GetWorldLocationAtSplinePoint(CurrentWaypointIndex);
}
