// Copyright Nicholas Reardon


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	// if (const AAuraPlayerState* PlayerState = PlayerState())
	// {
	// 	if (const UAuraAttributeSet* AttributeSet = Cast<UAuraAttributeSet>(PlayerState->GetAttributeSet()))		{
	// 		OnHealthChanged.Broadcast(AttributeSet->GetHealth());
	// 		OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHealth());
	// 		OnManaChanged.Broadcast(AttributeSet->GetMana());
	// 		OnMaxManaChanged.Broadcast(AttributeSet->GetMaxMana());
	// 	}
	// }

	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}
