// © 2014 - 2016 Soverance Studios
// http://www.soverance.com

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Ethereal.h"
#include "DeathCap.h"

ADeathCap::ADeathCap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/GiantMushroom/GiantMushroomMesh.GiantMushroomMesh'"));
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/GiantMushroom/Anim_GiantMushroom.Anim_GiantMushroom'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> UpheavalParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_Aura/Mushroom_Pulse.Mushroom_Pulse'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AggroAudioObject(TEXT("SoundCue'/Game/Audio/Party/GiantMushroom_Aggro_Cue.GiantMushroom_Aggro_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SpitAudioObject(TEXT("SoundCue'/Game/Audio/Party/GiantMushroom_Attack1_Cue.GiantMushroom_Attack1_Cue'"));

	// Set Default Objects
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object->GetAnimBlueprintGeneratedClass());
	
	// DEFAULTS
	Name = EEnemyNames::EN_DeathCap;
	Realm = ERealms::R_Shiitake;
	BattleType = EBattleTypes::BT_Boss;	
	CommonDrop = EMasterGearList::GL_Adrenaline;
	UncommonDrop = EMasterGearList::GL_HiPotion;
	RareDrop = EMasterGearList::GL_Claymore;
	AttackDelay = 2.0f;
	BaseEyeHeight = 16;
	AttackDelay = 2.0f;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(1, 1, 1));
	GetCharacterMovement()->MaxAcceleration = 0;

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 300;
	PawnSensing->LOSHearingThreshold = 400;
	PawnSensing->SightRadius = 750;
	PawnSensing->SetPeripheralVisionAngle(50.0f);
	AcceptanceRadius = 100.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object->GetAnimBlueprintGeneratedClass());
	GetMesh()->SetRelativeScale3D(FVector(2, 2, 2));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Melee Radius Config
	MeleeRadius->SetSphereRadius(70);
	MeleeRadius->SetRelativeLocation(FVector(15, 0, 0));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 150));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	// Hit & Death Effect Config
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Configure components
	UpheavalFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("UpheavalFX"));
	P_UpheavalFX = UpheavalParticleObject.Object;
	UpheavalFX->Template = P_UpheavalFX;
	UpheavalFX->bAutoActivate = false;

	AggroAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AggroAudio"));
	S_AggroAudio = AggroAudioObject.Object;
	AggroAudio->Sound = S_AggroAudio;
	AggroAudio->bAutoActivate = false;

	SpitAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SpitAudio"));
	S_SpitAudio = SpitAudioObject.Object;
	SpitAudio->Sound = S_SpitAudio;
	SpitAudio->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ADeathCap::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &ADeathCap::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &ADeathCap::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &ADeathCap::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &ADeathCap::AttackCycle);  // bind the attack function to the OnReachedTarget event
}

void ADeathCap::Death()
{
	//FinalDeath(true, false);
}

void ADeathCap::AttackCycle()
{

}

void ADeathCap::PoisonLob()
{
	EnemyDealDamage(30); // get damage output
	Spit = true;  // do the spit animation
	// TO DO :  spawn the mushroom poison lob drop
	// TO DO :  call the "DoLob" function inside the lob drop, passing the damage output of this actor
	// TO DO :  wait the attack delay, and call the RunToTarget() function
}

void ADeathCap::PoisonUpheaval()
{
	Roar = true;  // do the roar animation
	// TO DO :  set the Upheaval decal to visible, which has not yet been added to the constructor, so you need to do that too.
	// Delay one second
	UpheavalFX->Activate();

	// TO DO :  needs a specific collider, which will then check if a player is inside, and if so, have that player take damage
	// TO DO :  call the poison status function on the player
	// TO DO :  wait the attack delay, and call the RunToTarget() function
}

void ADeathCap::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{

	const FString VolumeDesc = FString::Printf(TEXT(" at volume %f"), Volume);
	FString message = TEXT("Heard Actor ") + PawnInstigator->GetName() + VolumeDesc;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);

	// TO DO: game-specific logic    
}

void ADeathCap::OnSeePawn(APawn* Pawn)
{
	if (!IsAggroed)
	{
		Aggro(Pawn);
		Roar = true;

		//RunToTarget() after the Roar. This timer is not needed because this function was tied to an anim notify in Roar
		//FTimerHandle DestroyTimer;
		//GetWorldTimerManager().SetTimer(DestroyTimer, this, &AEtherealEnemyMaster::RunToTarget, 3.0f, false);	
	}
}
