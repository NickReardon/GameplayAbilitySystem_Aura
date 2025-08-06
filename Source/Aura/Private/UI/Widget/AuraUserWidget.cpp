// Copyright Nicholas Reardon


#include "UI/Widget/AuraUserWidget.h"

#include "UI/WidgetController/OverlayWidgetController.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();

	// Cast<UOverlayWidgetController>(WidgetController)->MessageWidgetRowDelegate.AddLambda(
	// 	[this](FUIWidgetRow& Row)
	// 	{
	// 		if (Row.MessageWidget)
	// 		{
	// 			UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), Row.MessageWidget);
	// 			if (Widget)
	// 			{
	// 				Widget->AddToViewport();
	// 				// Optionally, you can set the message text or image here
	// 				// Widget->SetMessage(Row.Message);
	// 			}
	// 		}
	// 	}
	// );
}