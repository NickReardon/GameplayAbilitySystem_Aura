// Copyright Nicholas Reardon


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::Initialize(const FWidgetControllerParameters& Parameters)
{
	PlayerController = Parameters.PlayerController;
	PlayerState = Parameters.PlayerState;
	AbilitySystemComponent = Parameters.AbilitySystemComponent;
	AttributeSet = Parameters.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
}
