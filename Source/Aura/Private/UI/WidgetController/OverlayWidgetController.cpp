// Copyright Nicholas Reardon


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	
	OnHealthChanged.Broadcast(AbilitySystemComponent->GetNumericAttribute(AuraAttributeSet->GetHealthAttribute()));
	OnMaxHealthChanged.Broadcast(AbilitySystemComponent->GetNumericAttribute(AuraAttributeSet->GetMaxHealthAttribute()));
	OnManaChanged.Broadcast(AbilitySystemComponent->GetNumericAttribute(AuraAttributeSet->GetManaAttribute()));
	OnMaxManaChanged.Broadcast(AbilitySystemComponent->GetNumericAttribute(AuraAttributeSet->GetMaxManaAttribute()));
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	BindAttributeChangedDelegate<float>(AuraAttributeSet->GetHealthAttribute(), OnHealthChanged);
	BindAttributeChangedDelegate<float>(AuraAttributeSet->GetMaxHealthAttribute(), OnMaxHealthChanged);
	BindAttributeChangedDelegate<float>(AuraAttributeSet->GetManaAttribute(), OnManaChanged);
	BindAttributeChangedDelegate<float>(AuraAttributeSet->GetMaxManaAttribute(), OnMaxManaChanged);
	

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			const FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			for (const FGameplayTag& Tag : AssetTags)
			{
				// "A.1".matchesTag(FGameplayTag("A")) is true, but "A".matchesTag(FGameplayTag("A.1")) is false
				if (!Tag.MatchesTag(MessageTag))
					continue;
					
				FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				MessageWidgetRowDelegate.Broadcast(*Row);
			}
		}
	);
}

