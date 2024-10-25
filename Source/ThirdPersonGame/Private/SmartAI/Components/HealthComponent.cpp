#include "SmartAI/Components/HealthComponent.h"

#include "MathUtil.h"

void UHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
									class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Health == 0) return;

	Health -= Damage;
	Health = FMathf::Clamp(Health, 0 ,MaxHealth);
	HealthChanged.Broadcast(GetHealthPercent(), GetHealthString());

	if (IsBlocking)
	{
		BlockedDelegate.Broadcast();
	}

	HitResponseDelegate.Broadcast(IsInterruptible);

	if (Health == 0)
	{
		DeathDelegate.Broadcast();
	}

	if(DebugMessage)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3, FColor::Red, FString::Printf(TEXT("[%s] Health: %s"), *Owner->GetActorNameOrLabel(), *GetHealthString()));
	}
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<APawn>(GetOwner());

	if (!Owner) return;

	Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);

	InitializeHealth();
}

void UHealthComponent::InitializeHealth()
{
	Health = MaxHealth;
}

