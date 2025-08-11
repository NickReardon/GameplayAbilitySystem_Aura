// Copyright Nicholas Reardon


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"



void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	//Super::BindCallbacksToDependencies();
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	checkf(AttributeInfo, TEXT("AttributeInfo uninitialized. Please fill out BP_AttributeMenuWidgetController in the editor."));

	for ( auto& Pair : AS->TagsToAttributes )
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data)
		{
			if (Data.Attribute == Pair.Value())
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
		}
		);
	}

}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	//Super::BroadcastInitialValues();
    UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
    
    checkf(AttributeInfo, TEXT("AttributeInfo uninitialized. Please fill out BP_AttributeMenuWidgetController in the editor."));
    
    for (auto& Pair : AS->TagsToAttributes)
    {
    	BroadcastAttributeInfo(Pair.Key, Pair.Value());
    }

}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}