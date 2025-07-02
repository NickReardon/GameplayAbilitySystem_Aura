// Copyright Nicholas Reardon

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
