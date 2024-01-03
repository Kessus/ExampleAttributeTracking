// "// Copyright 2019 - 2021 AFK Studio"

#pragma once

#include "CoreMinimal.h"
#include "ExampleAbilitySystemComponent.h"
#include "AttributeTrackingResponseBase.h"
#include "GameplayTagContainer.h"
#include "Object.h"
#include "AttributeTrackingTagResponse.generated.h"

/**
 * Adds a replicated tag when the response begins. Removes the tag when response ends.
 */
UCLASS()
class EXAMPLE_API UAttributeTrackingTagResponse : public UAttributeTrackingResponseBase
{
	GENERATED_BODY()

public:
	UAttributeTrackingTagResponse* Init(FGameplayTag TagToSetAsResponse, UExampleAbilitySystemComponent* AbilitySystemComponent);
	
	virtual void Begin(float ChangeAmount) override;
	virtual void End() override;

protected:
	FGameplayTag ResponseTag;
	UPROPERTY()
	UExampleAbilitySystemComponent* AbilitySystem;
};
