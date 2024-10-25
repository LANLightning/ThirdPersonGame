// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/DefaultPlayerController.h"
#include "EnhancedInputSubsystems.h"

void ADefaultPlayerController::AddInputMappingContext(UInputMappingContext* InputMappingContext)
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem == nullptr) return;

	Subsystem->AddMappingContext(InputMappingContext, 0);
	ActiveInputMappingContext = InputMappingContext;
}

void ADefaultPlayerController::RemoveInputMappingContext(const UInputMappingContext* InputMappingContext) const
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	Subsystem->RemoveMappingContext(InputMappingContext);
}

void ADefaultPlayerController::DisableInput(APlayerController* PlayerController)
{
	Super::DisableInput(PlayerController);

	RemoveInputMappingContext(ActiveInputMappingContext);
}
