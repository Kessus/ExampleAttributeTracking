// "// Copyright 2019 - 2021 AFK Studio"


#include "TrackingConditions/BasicAttributeTrackingCondition.h"

#include "Kismet/KismetSystemLibrary.h"

UBasicAttributeTrackingCondition* UBasicAttributeTrackingCondition::Init(float RecentTime, EAttributeChangeType AttributeChangeType, float MinChangeAmount)
{
	RecentTimeSeconds = RecentTime;
	ChangeType = AttributeChangeType;
	MinimumChangeAmount = MinChangeAmount;

	return this;
}

bool UBasicAttributeTrackingCondition::ChangeFitsCondition(const FAttributeTrackingChangeInstance& ChangeInstance) const
{
	{
		if(!ChangeTypeMatches(ChangeInstance.ChangeAmount, ChangeType))
			return false;
		
		if(!MinimumChangeAmountMatches(ChangeInstance.ChangeAmount, MinimumChangeAmount))
			return false;
		
		if(!RecentTimeMatches(ChangeInstance.TrackingStartTime, RecentTimeSeconds))
			return false;
		
		return true;
	}
}
