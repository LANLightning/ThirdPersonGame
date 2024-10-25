#pragma once

#include "CoreMinimal.h"
#include "SmartAI/Characters/Enemy/BaseEnemy.h"
#include "RangedEnemy.generated.h"

UCLASS()
class THIRDPERSONGAME_API ARangedEnemy : public ABaseEnemy
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	FName EquipSocketName = FName(TEXT("Socket_WeaponSword"));

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	FName UnEquipSocketName = FName(TEXT("hand_rSocket"));

	UPROPERTY(EditAnywhere, Category = "Fire", meta = (AllowPrivateAccess = "true"))
	float Damage = 10;

	UPROPERTY(EditAnywhere, Category = "DEBUG", meta = (AllowPrivateAccess = "true"))
	bool DrawFireLine;
public:
	ARangedEnemy();

	void ToggleArmed();

	void Fire();

	bool LineTraceTarget(bool DrawDebug = false) const;
};
