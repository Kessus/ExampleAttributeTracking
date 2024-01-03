// "// Copyright 2019 - 2021 AFK Studio"


#include "TrackingDirectives/AttributeTrackingDirectiveBase.h"

TMap<FGameplayAttribute, FAttributeTrackingDescriptionCollection> UAttributeTrackingDirectiveBase::GetAttributeTrackingMap()
{
	return AttributeTrackingMap;
}
