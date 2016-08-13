// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#include "Ethereal.h"
#include "HiEther.h"

// Sets default values
AHiEther::AHiEther(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/Ethereal_Elixer_Cue.Ethereal_Elixer_Cue'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObject(TEXT("ParticleSystem'/Game/EtherealParty/OldWizard/Effects/Item_UsePotion.Item_UsePotion'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Hi-Ether.ItemIcon_Hi-Ether'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Hi-Ether-small.ItemIcon_Hi-Ether-small'"));

	// Set Default Objects

	Name = EMasterGearList::GL_HiEther;
	Type = EMasterGearTypes::GT_Consumable;
	Effect = "+ 65% of Max MP";
	Description = "Restores a moderate portion of MP.";
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	S_ItemAudio = AudioObject.Object;
	P_ItemFX = ParticleObject.Object;

}

// Called when the game starts or when spawned
void AHiEther::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	OnItemUse.AddDynamic(this, &AHiEther::Use);

	ItemFX->Template = P_ItemFX;
	ItemFX->bAutoActivate = false;
	ItemAudio->Sound = S_ItemAudio;
	ItemAudio->bAutoActivate = false;
}

void AHiEther::Use()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "An Item Was Used.");

	// Activate ItemFX
	// Play ItemAudio
	// Player State Reference
	// MP_Current = MP_Current + (MP_Max * 0.65)
	// Force MP Caps
	// Show Combat Text MP Restore
}


