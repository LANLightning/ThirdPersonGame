#include "Utilities/Utility.h"

#include "Camera/CameraComponent.h"

void UUtility::LineTraceFromCamera(FHitResult& HitResult, FVector& SocketLocation, FVector& TracedLocation, const UCameraComponent* CameraComponent, const USkeletalMeshComponent* SkeletalMeshComponent, const FString SocketName, ECollisionChannel TraceChannel, const float TraceRange, const bool IgnoreCameraOwner, const bool TraceComplex, const bool ShouldDrawDebug, const float DrawTime)
{
	SocketLocation = SkeletalMeshComponent->GetSocketTransform(FName(SocketName)).GetLocation();

	const UWorld* World = CameraComponent->GetWorld();
	const FVector LineStartForCamera = CameraComponent->GetComponentLocation();
	const FVector LineEndForCamera = LineStartForCamera + CameraComponent->GetForwardVector() * TraceRange;
	FCollisionQueryParams Params;
	Params.bTraceComplex = TraceComplex;
	if (IgnoreCameraOwner)
	{
		Params.AddIgnoredActor(CameraComponent->GetOwner()->GetUniqueID());
	}
	FHitResult CameraHitResult;
	World->LineTraceSingleByChannel(CameraHitResult, LineStartForCamera, LineEndForCamera, TraceChannel, Params);
	const FVector CameraTraceEndLocation = CameraHitResult.bBlockingHit ? CameraHitResult.Location : LineEndForCamera;
	const FVector LineStartForSkillTrace = CameraComponent->GetOwner()->GetActorLocation();
	const FVector LineEndForSkillTrace = LineStartForSkillTrace + (CameraTraceEndLocation - LineStartForSkillTrace);

	World->LineTraceSingleByChannel(HitResult, LineStartForSkillTrace, LineEndForSkillTrace, TraceChannel, Params);

	TracedLocation = HitResult.bBlockingHit ? HitResult.Location : LineEndForSkillTrace;

	if (ShouldDrawDebug && DrawTime)
	{
		if (HitResult.bBlockingHit)
		{
			DrawDebugLine(World, LineStartForSkillTrace, TracedLocation, FColor::Green, false, DrawTime);
			DrawDebugLine(World, TracedLocation, LineEndForSkillTrace, FColor::Red, false, DrawTime);
			DrawDebugSphere(World, TracedLocation, 10, 16, FColor::Blue, false, DrawTime);
		}
		else
		{
			DrawDebugLine(World, LineStartForSkillTrace, LineEndForSkillTrace, FColor::Red, false, DrawTime);
		}
	}
}

//FVector UUtility::LineTraceFromCamera(FHitResult& HitResult, const UCameraComponent* CameraComponent,
//	const ECollisionChannel TraceChannel, const float TraceRange, const bool IgnoreCameraOwner, const bool TraceComplex,
//	const bool ShouldDrawDebug, const float DrawTime)
//{
//	const UWorld* World = CameraComponent->GetWorld();
//	const FVector LineStart = CameraComponent->GetOwner()->GetActorLocation();
//	const FVector LineEnd = LineStart + CameraComponent->GetForwardVector() * TraceRange;
//	FCollisionQueryParams Params;
//	Params.bTraceComplex = TraceComplex;
//
//	if (IgnoreCameraOwner)
//	{
//		Params.AddIgnoredActor(CameraComponent->GetOwner()->GetUniqueID());
//	}
//
//	World->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, TraceChannel, Params);
//
//	const FVector TracedLocation = HitResult.bBlockingHit ? HitResult.Location : LineEnd;
//
//	if (ShouldDrawDebug && DrawTime)
//	{
//		if (HitResult.bBlockingHit)
//		{
//			DrawDebugLine(World, LineStart, TracedLocation, FColor::Green, false, DrawTime);
//			DrawDebugLine(World, TracedLocation, LineEnd, FColor::Red, false, DrawTime);
//			DrawDebugSphere(World, TracedLocation, 10, 16, FColor::Blue, false, DrawTime);
//		}
//		else
//		{
//			DrawDebugLine(World, LineStart, LineEnd, FColor::Red, false, DrawTime);
//		}
//	}
//
//	return TracedLocation;
//}
