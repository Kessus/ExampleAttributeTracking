// "// Copyright 2019 - 2021 AFK Studio"

#pragma once

#include "CoreMinimal.h"
#include "AttributeTrackingDirectiveBase.h"
#include "PlayerAttributeTrackingDirective.generated.h"

class UExampleAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class EXAMPLE_API UPlayerAttributeTrackingDirective : public UAttributeTrackingDirectiveBase
{
	GENERATED_BODY()

public:
	UPlayerAttributeTrackingDirective* Init(UExampleAbilitySystemComponent* AbilitySystemComponent);
	virtual UAttributeTrackingDirectiveBase* BuildDirective() override;

protected:
	UPROPERTY()
	UAttributeTrackingManager* TrackingManager;
	UPROPERTY()
	UExampleAbilitySystemComponent* AbilitySystem;
};
