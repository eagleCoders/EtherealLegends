// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#include "Ethereal.h"
#include "Elixer.h"

// Sets default values
AElixer::AElixer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/Ethereal_Elixer_Cue.Ethereal_Elixer_Cue'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObject(TEXT("ParticleSystem'/Game/EtherealParty/OldWizard/Effects/Item_UsePotion.Item_UsePotion'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Elixer.ItemIcon_Elixer'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Elixer-small.ItemIcon_Elixer-small'"));

	// Set Default Objects

	Name = EMasterGearList::GL_Elixer;
	Type = EMasterGearTypes::GT_Consumable;
	Effect = "+ Full Restore";
	Description = "Instantly restores HP and MP to full capacity.";
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	S_ItemAudio = AudioObject.Object;
	P_ItemFX = ParticleObject.Object;
	
}

// Called when the game starts or when spawned
void AElixer::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	OnItemUse.AddDynamic(this, &AElixer::Use);

	ItemFX->Template = P_ItemFX;
	ItemFX->bAutoActivate = false;
	ItemAudio->Sound = S_ItemAudio;
	ItemAudio->bAutoActivate = false;	
}

void AElixer::Use()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "An Item Was Used.");
}


