// Copyright Nicholas Reardon


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::InitializePrimaryAttributes() const
{	
	if (!DefaultPrimaryAttributes)
	{
		UE_LOG(LogTemp, Warning, TEXT("DefaultPrimaryAttributes is not set for %s"), *GetName());
		return;
	}
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		const FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
		const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.0f, EffectContextHandle);
		ASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), ASC);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AbilitySystemComponent is not set for %s"), *GetName());
	}
}

