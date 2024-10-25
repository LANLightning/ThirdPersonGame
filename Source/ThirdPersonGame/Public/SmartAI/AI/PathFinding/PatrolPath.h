#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPath.generated.h"

class USplineComponent;

UCLASS()
class THIRDPERSONGAME_API APatrolPath : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USplineComponent> SplineComponent;

	int32 CurrentWaypointIndex;
	int32 Direction = 1;

protected:
	virtual void BeginPlay() override;

public:
	APatrolPath();

	void UpdateWaypoint();

	FVector GetWaypoint() const;
};
