#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVoidDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBoolDelegate, bool, BoolParam);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthChangedDelegate, const float, HealthPercent, const FString&, HealthString);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	float Health;

	UPROPERTY(EditAnywhere, Category = "Components|Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100;

	UPROPERTY(EditAnywhere, Category = "DEBUG", meta = (AllowPrivateAccess = "true"))
	bool DebugMessage = false;

	UPROPERTY(EditAnywhere, Category = "Status", meta = (AllowPrivateAccess = "true"))
	bool IsInvincible;

	UPROPERTY(EditAnywhere, Category = "Status", meta = (AllowPrivateAccess = "true"))
	bool IsInterruptible;

	UPROPERTY(EditAnywhere, Category = "Status", meta = (AllowPrivateAccess = "true"))
	bool IsBlocking;

	UPROPERTY()
	TObjectPtr<APawn> Owner;

protected:
	UFUNCTION()
	virtual void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	virtual void BeginPlay() override;

public:	
	FHealthChangedDelegate HealthChanged;

	FVoidDelegate DeathDelegate;
	FVoidDelegate BlockedDelegate;
	FBoolDelegate HitResponseDelegate;

	virtual void InitializeHealth();

	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetHealthPercent() const { return Health / MaxHealth; }
	FORCEINLINE FString GetHealthString() const { return FString::Printf(TEXT("%.0f / %.0f"), Health, MaxHealth); }

	FORCEINLINE bool GetIsInvincible() const { return IsInvincible; }
	FORCEINLINE void SetIsInvincible(const bool InValue) { IsInvincible = InValue; }
	FORCEINLINE bool GetIsInterruptible() const { return IsInterruptible; }
	FORCEINLINE void SetIsInterruptible(const bool InValue) { IsInterruptible = InValue; }
	FORCEINLINE bool GetIsBlocking() const { return IsBlocking; }
	FORCEINLINE void SetIsBlocking(const bool InValue) { IsBlocking = InValue; }
};
