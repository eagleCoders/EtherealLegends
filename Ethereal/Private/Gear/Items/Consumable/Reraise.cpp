// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#include "Ethereal.h"
#include "Reraise.h"

// Sets default values
AReraise::AReraise(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/Ethereal_Elixer_Cue.Ethereal_Elixer_Cue'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObject(TEXT("ParticleSystem'/Game/EtherealParty/OldWizard/Effects/Item_UsePotion.Item_UsePotion'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Revive.ItemIcon_Revive'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Revive-small.ItemIcon_Revive-small'"));

	// Set Default Objects

	Name = EMasterGearList::GL_Reraise;
	Type = EMasterGearTypes::GT_Consumable;
	Effect = "+ Reraise Effect";
	Description = "The power of the phoenix, granting life after death.";
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	S_ItemAudio = AudioObject.Object;
	P_ItemFX = ParticleObject.Object;

}

// Called when the game starts or when spawned
void AReraise::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	OnItemUse.AddDynamic(this, &AReraise::Use);

	ItemFX->Template = P_ItemFX;
	ItemFX->bAutoActivate = false;
	ItemAudio->Sound = S_ItemAudio;
	ItemAudio->bAutoActivate = false;
}

void AReraise::Use()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "An Item Was Used.");

	// DO NOT ACTIVATE ITEM FX, because it's attached to the character
	// Instead, spawn this particle effect at player location:  ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Cines/Ausar/P_Reraise.P_Reraise'
	// Play ItemAudio
	// Player State Reference
	// call "Server-RaiseStatus" event
}


