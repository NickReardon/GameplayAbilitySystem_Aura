// Copyright Nicholas Reardon


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	
	UAuraAssetManager* AssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	//FAuraGameplayTags::InitializeNativeTags();
	//UAbilitySystemGlobals::Get().InitGlobalData(); //Not necessary in UE5.3+
}
