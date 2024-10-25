#pragma once

#include "CoreMinimal.h"
#include "Utility.generated.h"

class UCameraComponent;

UCLASS()
class THIRDPERSONGAME_API UUtility : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Utilities", meta = (AdvancedDisplay = "TraceChannel, IgnoreCameraOwner, TraceComplex, DrawTime"))
	static void LineTraceFromCamera(
		FHitResult& HitResult,
		FVector& SocketLocation,
		FVector& TracedLocation,
		const UCameraComponent* CameraComponent,
		const USkeletalMeshComponent* SkeletalMeshComponent,
		const FString SocketName,
		const ECollisionChannel TraceChannel = ECC_Visibility,
		const float TraceRange = 3000,
		bool IgnoreCameraOwner = true,
		const bool TraceComplex = true,
		const bool ShouldDrawDebug = false,
		const float DrawTime = 3
	);

};
