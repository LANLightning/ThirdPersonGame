#include "SmartAI/UI/HealthBarWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "SmartAI/Components/HealthComponent.h"

void UHealthBarWidget::OnHealthChanged(const float HealthPercent, const FString& HealthString)
{
	HealthBar->SetPercent(HealthPercent);
	HealthTextBlock->SetText(FText::FromString(HealthString));
}

void UHealthBarWidget::SetUp(UHealthComponent* HealthComponent)
{
	HealthBar->SetPercent(HealthComponent->GetHealthPercent());
	HealthTextBlock->SetText(FText::FromString(HealthComponent->GetHealthString()));
	OnHealthChanged(HealthComponent->GetHealthPercent(), HealthComponent->GetHealthString());
	HealthComponent->HealthChanged.AddDynamic(this, &UHealthBarWidget::OnHealthChanged);
}
