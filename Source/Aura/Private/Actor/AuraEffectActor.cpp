// Copyright Nicholas Reardon


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootComponent"));


}



void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(TargetAbilitySystemComponent)) return;
	checkf(GameplayEffectClass, TEXT("GameplayEffectClass must be valid"));

	FGameplayEffectContextHandle EffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);
	TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
	
	/* Alternative approach using handles for infinite effects (commented out - tutorial approach)
	 * This approach provides more granular control by storing effect handles
	 * 
	 * // Store the active effect handle for infinite effects
	 * const FActiveGameplayEffectHandle ActiveEffectHandle = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	 * 
	 * // Check if this is an infinite effect
	 * const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	 * 
	 * // If infinite and we want to remove on end overlap, store the handle
	 * if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	 * {
	 *     ActiveEffectHandles.Add(ActiveEffectHandle, TargetAbilitySystemComponent);
	 * }
	 */
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(TargetAbilitySystemComponent)) return;
	
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		for (auto InstantEffectClass : InstantGameplayEffectClass)
			ApplyEffectToTarget(TargetActor, InstantEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		for (auto DurationEffectClass : DurationGameplayEffectClass)
			ApplyEffectToTarget(TargetActor, DurationEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		for (auto InfiniteEffectClass : InfiniteGameplayEffectClass)
			ApplyEffectToTarget(TargetActor, InfiniteEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(TargetAbilitySystemComponent)) return;
	
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		for (auto InstantEffect : InstantGameplayEffectClass)
			ApplyEffectToTarget(TargetActor, InstantEffect);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		for (auto DurationEffect : DurationGameplayEffectClass)
			ApplyEffectToTarget(TargetActor, DurationEffect);
	}

	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		for (auto InfiniteEffect : InfiniteGameplayEffectClass)
			TargetAbilitySystemComponent->RemoveActiveGameplayEffectBySourceEffect(InfiniteEffect, UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(this), 1);
	}
	
	/* Alternative approach using handles for infinite effects (commented out - tutorial approach)
	 * This approach removes effects by their stored handles for more precise control
	 * 
	 * if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	 * {
	 *     // Find and remove effects applied to this target
	 *     TArray<FActiveGameplayEffectHandle> HandlesToRemove;
	 *     
	 *     for (auto& HandlePair : ActiveEffectHandles)
	 *     {
	 *         if (HandlePair.Value == TargetAbilitySystemComponent)
	 *         {
	 *             // Remove the effect using its handle
	 *             TargetAbilitySystemComponent->RemoveActiveGameplayEffect(HandlePair.Key, 1);
	 *             HandlesToRemove.Add(HandlePair.Key);
	 *         }
	 *     }
	 *     
	 *     // Clean up the stored handles
	 *     for (const FActiveGameplayEffectHandle& Handle : HandlesToRemove)
	 *     {
	 *         ActiveEffectHandles.FindAndRemoveChecked(Handle);
	 *     }
	 * }
	 */
}