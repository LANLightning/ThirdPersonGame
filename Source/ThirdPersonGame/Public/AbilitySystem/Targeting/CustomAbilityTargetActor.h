#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "CustomAbilityTargetActor.generated.h"

UCLASS()
class THIRDPERSONGAME_API ACustomAbilityTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	TObjectPtr<APlayerController> CustomPrimaryPC;
	
	UPROPERTY()
	AGameplayAbilityWorldReticle* Reticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System", meta = (ExposeOnSpawn = "true"))
	float TraceRange = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System")
	FHitResult TraceResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System", meta = (ExposeOnSpawn = "true"))
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	void LineTrace(FHitResult& HitResult) const;

public:
	ACustomAbilityTargetActor();

	virtual void Tick(float DeltaSeconds) override;

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

	virtual void CancelTargeting() override;

	virtual AGameplayAbilityWorldReticle* SpawnReticle(FVector InLocation, FRotator InRotation);

	virtual void DestroyReticle();

};
