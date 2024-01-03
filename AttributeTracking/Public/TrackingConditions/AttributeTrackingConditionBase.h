// "// Copyright 2019 - 2021 AFK Studio"

#pragma once

#include "CoreMinimal.h"
#include "AttributeTrackingChangeInstance.h"
#include "AttributeTrackingConditionBase.generated.h"

enum class EAttributeChangeType : uint8
{
	Any,
	Positive,
	Negative
};

UCLASS()
class EXAMPLE_API UAttributeTrackingConditionBase : public UObject
{
	GENERATED_BODY()

public:
	virtual bool ChangeFitsCondition(const FAttributeTrackingChangeInstance& ChangeInstance) const PURE_VIRTUAL(UAttributeTrackingConditionBase::ChangeFitsCondition, return false;); 
	
protected:
	static bool RecentTimeMatches(const FDateTime& InstanceTrackingStartTime, float RecentTimeSeconds);
	static bool ChangeTypeMatches(float ChangeAmount, EAttributeChangeType AttributeChangeType);
	static bool MinimumChangeAmountMatches(float ChangeAmount, float MinimumChangeAmount);
	
};