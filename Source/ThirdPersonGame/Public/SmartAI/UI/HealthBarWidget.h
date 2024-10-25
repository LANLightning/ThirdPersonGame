#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class UTextBlock;
class UHealthComponent;
class UProgressBar;

UCLASS()
class THIRDPERSONGAME_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Widgets", meta=(BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UTextBlock* HealthTextBlock;

	UFUNCTION()
	void OnHealthChanged(float HealthPercent, const FString& HealthString);

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetUp(UHealthComponent* HealthComponent);

};
