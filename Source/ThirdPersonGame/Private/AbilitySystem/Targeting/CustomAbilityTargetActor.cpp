#include "AbilitySystem/Targeting/CustomAbilityTargetActor.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

ACustomAbilityTargetActor::ACustomAbilityTargetActor()
{
	PrimaryActorTick.bCanEverTick = true;
	//bDestroyOnConfirmation = true;
	ShouldProduceTargetDataOnServer = true;
	Reticle = nullptr;
}

void ACustomAbilityTargetActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	LineTrace(TraceResult);

	if (Reticle == nullptr || !PrimaryPC->IsLocalController())
		Reticle->SetActorHiddenInGame(true);

	Reticle->SetActorLocation(TraceResult.bBlockingHit ? TraceResult.ImpactPoint : TraceResult.TraceEnd);

	//if(Reticle && PrimaryPC->IsLocalController())
	//{
	//	Reticle->SetActorLocation(TraceResult.bBlockingHit ? TraceResult.ImpactPoint : TraceResult.TraceEnd);
	//}
	//else
	//{
	//	Reticle->SetActorHiddenInGame(true);
	//}
}

void ACustomAbilityTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	//Super::StartTargeting(Ability);

	OwningAbility = Ability;
	PrimaryPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
	Reticle = SpawnReticle(GetActorLocation(), GetActorRotation());
}

void ACustomAbilityTargetActor::ConfirmTargetingAndContinue()
{
	FHitResult HitResult;
	LineTrace(HitResult);
	const FGameplayAbilityTargetDataHandle TargetDataHandle = StartLocation.MakeTargetDataHandleFromHitResult(OwningAbility, HitResult);
	if (TargetDataHandle != nullptr)
	{
		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
	else
	{
		Super::ConfirmTargetingAndContinue();
	}

	DestroyReticle();
}

void ACustomAbilityTargetActor::CancelTargeting()
{
	Super::CancelTargeting();

	DestroyReticle();
}

AGameplayAbilityWorldReticle* ACustomAbilityTargetActor::SpawnReticle(FVector InLocation, FRotator InRotation)
{
	if (!ReticleClass) return nullptr;

	if (Reticle) return Reticle;

	AGameplayAbilityWorldReticle* SpawnedReticle = GetWorld()->SpawnActor<AGameplayAbilityWorldReticle>(ReticleClass, InLocation, InRotation);

	if (!SpawnedReticle) return nullptr;

	SpawnedReticle->InitializeReticle(this, PrimaryPC, ReticleParams);
	return SpawnedReticle;
}

void ACustomAbilityTargetActor::DestroyReticle()
{
	if (!Reticle) return;

	Reticle->Destroy();
}

void ACustomAbilityTargetActor::LineTrace(FHitResult& HitResult) const
{
	FVector LineStart;
	FRotator TraceRotation;
	PrimaryPC->GetPlayerViewPoint(LineStart, TraceRotation);
	FVector LineEnd = LineStart + TraceRotation.Vector() * TraceRange;
	const APawn* IgnoreActor = PrimaryPC->GetPawn();
	FCollisionQueryParams Params;
	Params.bTraceComplex = true;
	if(IgnoreActor)
		Params.AddIgnoredActor(IgnoreActor->GetUniqueID());

	GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, TraceChannel, Params);

	//DrawDebugSphere(GetWorld(), HitResult.Location, 30, 16, FColor::Yellow, false, 5.0f);
	//DrawDebugSphere(GetWorld(), LineEnd, 50, 16, FColor::Red, false, 5.0f);

}
