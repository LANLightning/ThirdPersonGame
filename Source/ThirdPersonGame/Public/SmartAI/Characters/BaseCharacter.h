#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "SmartAI/Enumeration/Faction.h"
#include "BaseCharacter.generated.h"

class UHealthComponent;
class ASmartAIEnemyControllerBase;
class UBaseAnimInstance;

UCLASS()
class THIRDPERSONGAME_API ABaseCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess))
	TObjectPtr<UHealthComponent> HealthComponent;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Faction", meta = (AllowPrivateAccess = "true"))
	EFaction Faction;

	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(static_cast<uint8>(Faction)); }

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void HealHealth( AActor* Healer, const float HealAmount);

	FORCEINLINE TObjectPtr<UHealthComponent> GetHealth() const { return HealthComponent; }
};
