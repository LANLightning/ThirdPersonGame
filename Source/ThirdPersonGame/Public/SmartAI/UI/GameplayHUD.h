#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameplayHUD.generated.h"

class UGameplayHUDWidgetForPlayer;

UCLASS()
class THIRDPERSONGAME_API AGameplayHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Widgets")
	TSubclassOf<UUserWidget> GameplayHUDWidgetClass;

	virtual void BeginPlay() override;

};
