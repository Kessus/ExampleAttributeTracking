// "// Copyright 2019 - 2021 AFK Studio"

#pragma once

#include "CoreMinimal.h"
#include "AttributeTrackingConditionBase.h"
#include "Object.h"
#include "BasicAttributeTrackingCondition.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPLE_API UBasicAttributeTrackingCondition : public UAttributeTrackingConditionBase
{
	GENERATED_BODY()

public:
	UBasicAttributeTrackingCondition* Init(float RecentTimeSeconds, EAttributeChangeType ChangeType = EAttributeChangeType::Any, float MinimumChangeAmount = 0.0f);
	virtual bool ChangeFitsCondition(const FAttributeTrackingChangeInstance& ChangeInstance) const override;

protected:
	float RecentTimeSeconds;
	EAttributeChangeType ChangeType;
	float MinimumChangeAmount;
};
