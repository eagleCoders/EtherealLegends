// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#pragma once

#include "Gear/Items/Item_Master.h"
#include "SentinelBrew.generated.h"

/**
 * 
 */
UCLASS()
class ETHEREAL_API ASentinelBrew : public AItem_Master
{
	GENERATED_BODY()

public:
	
	ASentinelBrew(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	/** Uses the item. */
	UFUNCTION(BlueprintCallable, Category = Controls)
	void Use();	
};
