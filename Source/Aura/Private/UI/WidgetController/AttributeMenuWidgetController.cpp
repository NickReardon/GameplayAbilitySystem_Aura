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
	
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AuraGameplayTags::TAG_ATTRIBUTES_PRIMARY_STRENGTH, true);
	Info.AttributeValue = AS->GetStrength();
	
	AttributeInfoDelegate.Broadcast(Info);
	
	
}
