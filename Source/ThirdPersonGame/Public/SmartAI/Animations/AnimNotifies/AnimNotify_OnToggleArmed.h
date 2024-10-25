#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_OnToggleArmed.generated.h"

UCLASS()
class THIRDPERSONGAME_API UAnimNotify_OnToggleArmed : public UAnimNotify
{
	GENERATED_BODY()

	//UPROPERTY(EditAnywhere, Category = "Socket", meta = (AllowPrivateAccess = "true"))
	//bool IsArmed;

	//UPROPERTY(EditAnywhere, Category = "Socket", meta = (AllowPrivateAccess = "true"))
	//FName WeaponSocketName;

protected:
	virtual FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
