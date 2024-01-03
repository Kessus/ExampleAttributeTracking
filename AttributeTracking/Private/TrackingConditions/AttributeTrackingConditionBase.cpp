// "// Copyright 2019 - 2021 AFK Studio"


#include "TrackingConditions/AttributeTrackingConditionBase.h"

bool UAttributeTrackingConditionBase::RecentTimeMatches(const FDateTime& InstanceTrackingStartTime, float RecentTimeSeconds)
{
	const float TicksSinceTrackingStart = (FDateTime::Now() - InstanceTrackingStartTime).GetTicks();
	return TicksSinceTrackingStart <= RecentTimeSeconds * ETimespan::TicksPerSecond;
}

bool UAttributeTrackingConditionBase::ChangeTypeMatches(float ChangeAmount, EAttributeChangeType AttributeChangeType)
{
	switch(AttributeChangeType) {
	case EAttributeChangeType::Any: return true;
	case EAttributeChangeType::Positive: return ChangeAmount > 0.0f;
	case EAttributeChangeType::Negative: return ChangeAmount < 0.0f;
	default:
		checkf(false, TEXT("Unsupported AttributeChangeType value"));
		return false;
	}
}

bool UAttributeTrackingConditionBase::MinimumChangeAmountMatches(float ChangeAmount, float MinimumChangeAmount)
{
	if(MinimumChangeAmount == 0.0f)
		return true;
		
	return ChangeAmount >= MinimumChangeAmount;
}
