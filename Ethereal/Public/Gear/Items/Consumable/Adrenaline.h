// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#pragma once

#include "Gear/Items/Item_Master.h"
#include "Adrenaline.generated.h"

/**
 * 
 */
UCLASS()
class ETHEREAL_API AAdrenaline : public AItem_Master
{
	GENERATED_BODY()
	
public:

	AAdrenaline(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	/** Uses the item. */
	UFUNCTION(BlueprintCallable, Category = Controls)
	void Use();	
};
