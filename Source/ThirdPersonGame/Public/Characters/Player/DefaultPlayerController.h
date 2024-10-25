// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class THIRDPERSONGAME_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY()
	UInputMappingContext* ActiveInputMappingContext;

public:
	UFUNCTION(BlueprintCallable)
	void AddInputMappingContext(UInputMappingContext* InputMappingContext);

	UFUNCTION(BlueprintCallable)
	void RemoveInputMappingContext(const UInputMappingContext* InputMappingContext) const;

	virtual void DisableInput(APlayerController* PlayerController) override;
};
