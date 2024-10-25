#include "SmartAI/UI/GameplayHUD.h"

#include "Blueprint/UserWidget.h"
#include "SmartAI/Characters/Player/SmartAIPlayerCharacter.h"
#include "SmartAI/Components/HealthComponent.h"
#include "SmartAI/UI/GameplayHUDWidgetForPlayer.h"
#include "SmartAI/UI/HealthBarWidget.h"


void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();

	ASmartAIPlayerCharacter* PlayerCharacter = Cast<ASmartAIPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!PlayerCharacter || !GameplayHUDWidgetClass) return;

	UGameplayHUDWidgetForPlayer* GameplayHUDWidget = CreateWidget<UGameplayHUDWidgetForPlayer>(GetWorld(), GameplayHUDWidgetClass);

	if (!GameplayHUDWidget) return;

	UHealthComponent* PlayerHealthComponent = PlayerCharacter->GetHealth();

	if (!PlayerHealthComponent) return;

	PlayerHealthComponent->InitializeHealth();
	GameplayHUDWidget->GetPlayerHealthBarWidget()->SetUp(PlayerHealthComponent);
	GameplayHUDWidget->AddToViewport();

}
