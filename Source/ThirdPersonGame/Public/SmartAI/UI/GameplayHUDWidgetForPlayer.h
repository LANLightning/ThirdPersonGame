#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayHUDWidgetForPlayer.generated.h"

class UHealthBarWidget;

UCLASS()
class THIRDPERSONGAME_API UGameplayHUDWidgetForPlayer : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UHealthBarWidget* PlayerHealthBarWidget;

public:
	UHealthBarWidget* GetPlayerHealthBarWidget() const { return PlayerHealthBarWidget; }
};
