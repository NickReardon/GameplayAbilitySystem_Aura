// Copyright Nicholas Reardon


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitMaxHealth(100.0f);
	InitHealth(50.0f);

	InitMaxMana(100.0f);
	InitMana(GetMaxMana());
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// Epic recommendation to only use PreAttributeChange for validation and clamping
	
	// Health attributes ---------------------------
	if (Attribute == GetHealthAttribute())
	{
		// Ensure health does not exceed max health
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());

		
		UE_LOG(LogTemp, Warning, TEXT("Health: %f"), GetHealth());
	}
	if (Attribute == GetMaxHealthAttribute())
	{
		// Ensure health does not exceed max health
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());

		
		UE_LOG(LogTemp, Warning, TEXT("Max Health: %f"), GetMaxHealth());
	}

	// Mana attributes ---------------------------
	if (Attribute == GetManaAttribute())
	{
		// Ensure mana does not exceed max mana
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
		
		UE_LOG(LogTemp, Warning, TEXT("Mana: %f"), GetMana());
	}
	if (Attribute == GetMaxManaAttribute())
	{
		// Ensure max mana is not less than current mana


		
		UE_LOG(LogTemp, Warning, TEXT("Max Mana: %f"), GetMaxMana());
	}


}


void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties EffectProperties;
	SetEffectProperties(Data, EffectProperties);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		const float OldHealth = GetHealth();
		const float NewHealth = GetHealth() + Data.EvaluatedData.Magnitude;
		SetHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		const float OldMaxHealth = GetMaxHealth();
		const float NewMaxHealth = GetMaxHealth() + Data.EvaluatedData.Magnitude;
		SetMaxHealth(FMath::Clamp(NewMaxHealth, 0.0f, FLT_MAX));
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		const float OldMana = GetMana();
		const float NewMana = GetMana() + Data.EvaluatedData.Magnitude;
		SetMana(FMath::Clamp(NewMana, 0.0f, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetMaxManaAttribute())
	{
		const float OldMaxMana = GetMaxMana();
		const float NewMaxMana = GetMaxMana() + Data.EvaluatedData.Magnitude;
		SetMaxMana(FMath::Clamp(NewMaxMana, 0.0f, FLT_MAX));
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProperties)
{
	const FGameplayEffectContextHandle EffectContextHandle = Data.EffectSpec.GetContext();
	EffectProperties.SourceASC = EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(EffectProperties.SourceASC) && EffectProperties.SourceASC->AbilityActorInfo.IsValid() && EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.SourceAvatarActor = EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.Get();
		EffectProperties.SourceController = EffectProperties.SourceASC->AbilityActorInfo->PlayerController.Get();

		if (EffectProperties.SourceController == nullptr && EffectProperties.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(EffectProperties.SourceAvatarActor))
			{
				EffectProperties.SourceController = Pawn->GetController();
			}
		}
		if (EffectProperties.SourceController)
		{
			EffectProperties.SourceCharacter = Cast<ACharacter>(EffectProperties.SourceController->GetPawn());
		}

	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProperties.TargetCharacter = Cast<ACharacter>(EffectProperties.TargetAvatarActor);
		EffectProperties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProperties.TargetAvatarActor);
	}


}
