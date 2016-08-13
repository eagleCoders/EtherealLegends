// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#include "Ethereal.h"
#include "Item_Master.h"

// Sets default values
AItem_Master::AItem_Master(const FObjectInitializer& ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//// Get Assets, References Obtained Via Right Click in Editor
	ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/Ethereal_Elixer_Cue.Ethereal_Elixer_Cue'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObject(TEXT("ParticleSystem'/Game/EtherealParty/OldWizard/Effects/Item_UsePotion.Item_UsePotion'"));
	//// Set Default Objects
	S_ItemAudio = AudioObject.Object;
	P_ItemFX = ParticleObject.Object;
	// Create
	ItemAudio = ObjectInitializer.CreateDefaultSubobject < UAudioComponent >(this, TEXT("Item Audio"));
	ItemFX = ObjectInitializer.CreateDefaultSubobject < UParticleSystemComponent >(this, TEXT("Item VFX"));
	//Effect = "None";
}

// Called when the game starts or when spawned
void AItem_Master::BeginPlay()
{
	Super::BeginPlay();

	// Attachment
	ItemAudio->SetupAttachment(GetRootComponent());
	ItemFX->SetupAttachment(GetRootComponent());
	ItemAudio->Sound = S_ItemAudio;
	ItemAudio->bAutoActivate = false;
	ItemFX->Template = P_ItemFX;
	ItemFX->bAutoActivate = false;
}

void AItem_Master::UseItem()
{
	OnItemUse.Broadcast();
}

