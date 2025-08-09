// Copyright Nicholas Reardon


#include "AuraGameplayTags.h"
// #include "GameplayTagsManager.h"
//
// FAuraGameplayTags FAuraGameplayTags::GameplayTags;
//
// void FAuraGameplayTags::InitializeNativeGameplayTags()
// {
// 	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improves Block Chance"));
//
// }

namespace AuraGameplayTags
{
	// Primary Attributes
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_PRIMARY_STRENGTH, "Attributes.Primary.Strength");
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_PRIMARY_INTELLIGENCE, "Attributes.Primary.Intelligence");
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_PRIMARY_RESILIENCE, "Attributes.Primary.Resilience");
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_PRIMARY_VIGOR, "Attributes.Primary.Vigor");
	
	// Secondary Attributes
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_SECONDARY_ARMOR, "Attributes.Secondary.Armor");
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_SECONDARY_ARMORPENETRATION, "Attributes.Secondary.ArmorPenetration");
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_SECONDARY_BLOCKCHANCE, "Attributes.Secondary.BlockChance");
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_SECONDARY_CRITICALHITCHANCE, "Attributes.Secondary.CriticalHitChance");
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_SECONDARY_CRITICALHITDAMAGE, "Attributes.Secondary.CriticalHitDamage");
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_SECONDARY_CRITICALHITRESISTANCE, "Attributes.Secondary.CriticalHitResistance");
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_SECONDARY_HEALTHREGENERATION, "Attributes.Secondary.HealthRegeneration");
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_SECONDARY_MANAREGENERATION, "Attributes.Secondary.ManaRegeneration");
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_VITAL_MAXHEALTH, "Attributes.Secondary.MaxHealth");
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_VITAL_MAXMANA, "Attributes.Secondary.MaxMana");
	
	// Vital Attributes
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_VITAL_HEALTH, "Attributes.Vital.Health");
	UE_DEFINE_GAMEPLAY_TAG(TAG_ATTRIBUTES_VITAL_MANA, "Attributes.Vital.Mana");
}
