// "// Copyright 2019 - 2021 AFK Studio"

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeTrackingConditionBase.h"
#include "Object.h"
#include "AttributeTrackingResponseBase.generated.h"

class UAttributeTrackingManager;

/**
 * 
 */
UCLASS()
class EXAMPLE_API UAttributeTrackingResponseBase : public UObject
{
	GENERATED_BODY()
public:
	
	float GetLastRegisteredValue() const;
	bool ResponseHasBegun() const;
	virtual void Begin(float ChangeAmount);
	virtual void Update(float ChangeAmount);
	virtual void End();

protected:

	float LastRegisteredValue = 0.0f;
	bool HasBegun = false;
};

