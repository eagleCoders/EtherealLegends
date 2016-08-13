// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#include "Ethereal.h"
#include "Adrenaline.h"

// Sets default values
AAdrenaline::AAdrenaline(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	//ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/Ethereal_Elixer_Cue.Ethereal_Elixer_Cue'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObject(TEXT("ParticleSystem'/Game/EtherealParty/OldWizard/Effects/Item_UsePotion.Item_UsePotion'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Adrenaline.ItemIcon_Adrenaline'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Adrenaline-small.ItemIcon_Adrenaline-small'"));

	// Set Default Objects

	Name = EMasterGearList::GL_Adrenaline;
	Type = EMasterGearTypes::GT_Consumable;	
	Effect = "+ 20% ATK for 120 Seconds";
	Description = "Grants an attack boost for a limited time.";
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	//S_ItemAudio = AudioObject.Object;
	P_ItemFX = ParticleObject.Object;
	ItemFX->Template = P_ItemFX;
	ItemFX->bAutoActivate = false;
	//ItemAudio->Sound = S_ItemAudio;
	//ItemAudio->bAutoActivate = false;	
}

// Called when the game starts or when spawned
void AAdrenaline::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	OnItemUse.AddDynamic(this, &AAdrenaline::Use);
	
}

void AAdrenaline::Use()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "An Item Was Used.");
}

