#pragma once

#include "CoreMinimal.h"
#include "DefaultPlayerController.h"
#include "Characters/Base/CharacterBase.h"
#include "PlayerCharacter.generated.h"


//struct FGameplayTag;
//struct FOnAttributeChangeData;
class UCameraComponent;
class USpringArmComponent;
UCLASS()
class THIRDPERSONGAME_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Params|Camera", meta = (AllowPrivateAccess = "true"))
	float DefaultSpringArmLength;
	UPROPERTY(BlueprintReadOnly, Category = "Params|Camera", meta = (AllowPrivateAccess = "true"))
	FVector DefaultSpringArmRelativeLocation;

	UPROPERTY(EditAnywhere, Category = "DEBUG")
	float DefaultMaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = "DEBUG")
	float DefaultMaxMana = 100.0f;

	UPROPERTY(EditAnywhere, Category = "DEBUG")
	float DefaultMaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, Category = "DEBUG")
	uint16 DefaultLevel = 1;

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	ADefaultPlayerController* DefaultPlayerController;

	virtual void OnRep_PlayerState() override;

#pragma region Input Functions
	UFUNCTION(BlueprintCallable)
	void Look(const FVector2D& InputValue);

	UFUNCTION(BlueprintCallable)
	void Zoom(float InputValue);

	UFUNCTION(BlueprintCallable)
	void Move(const FVector2D& InputValue);
#pragma endregion

#pragma region Helper Functions
	void InitializeLevel(const uint16 InLevel) const;
	void InitializeHealth(const float InHealth, const float InMaxHealth) const;
	void InitializeMana(const float InMana, const float InMaxMana) const;
	void InitializeStamina(const float InStamina, const float InMaxStamina) const;
#pragma endregion

public:
	virtual void PossessedBy(AController* NewController) override;

	USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }

	UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	float GetDefaultSpringArmLength() const { return DefaultSpringArmLength; }

	FVector GetDefaultSpringArmRelativeLocation() const { return DefaultSpringArmRelativeLocation; }

	virtual void Die() override;
};
