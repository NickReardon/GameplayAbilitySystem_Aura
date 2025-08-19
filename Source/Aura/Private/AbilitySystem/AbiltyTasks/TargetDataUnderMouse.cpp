// Copyright Nicholas Reardon


#include "AbilitySystem/AbiltyTasks/TargetDataUnderMouse.h"

#include "Kismet/GameplayStatics.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	FHitResult HitResult;
	Ability->GetCurrentActorInfo()->PlayerController.Get()->
		GetHitResultUnderCursor(ECC_GameTraceChannel1, false, HitResult);

	ValidData.Broadcast(HitResult.Location);
}
