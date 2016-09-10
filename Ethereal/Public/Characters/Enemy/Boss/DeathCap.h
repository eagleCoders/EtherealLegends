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

#pragma once

#include "Characters/Enemy/EtherealEnemyMaster.h"
#include "DeathCap.generated.h"

UCLASS()
class ETHEREAL_API ADeathCap : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ADeathCap(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Aggro Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* AggroAudio;
	USoundCue* S_AggroAudio;

	// Spit Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* SpitAudio;
	USoundCue* S_SpitAudio;

	/** Poison Upheaval */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* UpheavalFX;
	UParticleSystem* P_UpheavalFX;
	
	// Roar - play the aggro roar animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool Roar;

	// Spit - do the poison spit lob attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool Spit;

	// Denotes whether the mushroom is above or below ground. If Hiding is true, only the mushroom cap is visible to the player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool Hiding;

	// Death
	UFUNCTION(BlueprintCallable, Category = Default)
	void Death();

	////////////////////////////////////////
	// ATTACK CYCLE

	// Poison Lob Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void AttackCycle();

	// Poison Lob Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void PoisonLob();

	// Poison Upheaval Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void PoisonUpheaval();

	///////////////////////////
	// A.I.

	// Called when seeing a pawn
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	// Called when hearing noise
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
};
