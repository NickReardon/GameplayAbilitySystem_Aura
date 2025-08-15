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
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_PRIMARY_STRENGTH, "Attributes.Primary.Strength", "Increases physical damage");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_PRIMARY_INTELLIGENCE, "Attributes.Primary.Intelligence", "Increases magical damage");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_PRIMARY_RESILIENCE, "Attributes.Primary.Resilience", "Increases armor and armor penetration");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_PRIMARY_VIGOR, "Attributes.Primary.Vigor", "Increases health");

	// Secondary Attributes
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_ARMOR, "Attributes.Secondary.Armor", "Reduces damage taken, improves block chance");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_ARMORPENETRATION, "Attributes.Secondary.ArmorPenetration", "Ignores percentage of enemy armor, increases critical hit chance");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_BLOCKCHANCE, "Attributes.Secondary.BlockChance", "Chance to cut incoming damage in half");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_CRITICALHITCHANCE, "Attributes.Secondary.CriticalHitChance", "Chance to double damage plus critical hit bonus");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_CRITICALHITDAMAGE, "Attributes.Secondary.CriticalHitDamage", "Bonus damage added when a critical hit is scored");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_CRITICALHITRESISTANCE, "Attributes.Secondary.CriticalHitResistance", "Reduces critical hit chance of attacking enemies");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_HEALTHREGENERATION, "Attributes.Secondary.HealthRegeneration", "Amount of health regenerated every 1 second");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_MANAREGENERATION, "Attributes.Secondary.ManaRegeneration", "Amount of mana regenerated every 1 second");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_MAXHEALTH, "Attributes.Secondary.MaxHealth", "Maximum amount of health obtainable");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_SECONDARY_MAXMANA, "Attributes.Secondary.MaxMana", "Maximum amount of mana obtainable");

	// Vital Attributes
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_VITAL_HEALTH, "Attributes.Vital.Health", "Amount of damage a player can take before death");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_ATTRIBUTES_VITAL_MANA, "Attributes.Vital.Mana", "A resource used to cast spells");
	
	// Input Tags
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_INPUTTAG_LMB, "InputTag.LMB", "Left Mouse Button");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_INPUTTAG_RMB, "InputTag.RMB", "Right Mouse Button");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_INPUTTAG_1, "InputTag.1", "Placeholder for InputTag.1, used for abilities or actions");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_INPUTTAG_2, "InputTag.2", "Placeholder for InputTag.2, used for abilities or actions");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_INPUTTAG_3, "InputTag.3", "Placeholder for InputTag.3, used for abilities or actions");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_INPUTTAG_4, "InputTag.4", "Placeholder for InputTag.4, used for abilities or actions");
}
 