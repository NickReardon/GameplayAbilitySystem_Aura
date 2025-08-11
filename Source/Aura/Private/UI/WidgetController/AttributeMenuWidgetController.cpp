// Copyright Nicholas Reardon


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	//Super::BroadcastInitialValues();
	
	
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	//Super::BindCallbacksToDependencies();
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	checkf(AttributeInfo, TEXT("AttributeInfo uninitialized. Please fill out BP_AttributeMenuWidgetController in the editor."));
	
	for (TPair<FGameplayTag, FGameplayAttribute(*)()>& Pair : AS->TagsToAttributes)
	{
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key, true); // Contains the attribute tag, name, description, and default value
		Info.AttributeValue = Pair.Value().GetNumericValue(AS); // Get the current value of the attribute from the AttributeSet

		AttributeInfoDelegate.Broadcast(Info);
	}
}
