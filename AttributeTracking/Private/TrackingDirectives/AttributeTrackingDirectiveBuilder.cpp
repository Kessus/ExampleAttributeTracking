// "// Copyright 2019 - 2021 AFK Studio"


#include "AttributeTrackingDirectiveBuilder.h"

TMap<FGameplayAttribute, FAttributeTrackingDescriptionCollection> FAttributeTrackingDirectiveBuilder::ToTrackingDescriptionMap()
{
	return AttributeTrackingMap;
}

FAttributeTrackingDirectiveBuilder* FAttributeTrackingDirectiveBuilder::ForAttribute(FGameplayAttribute Attribute)
{
	CurrentAttribute = Attribute;
	BeginNewTrackingDescriptionCollection();
	
	return this;
}

FAttributeTrackingDirectiveBuilder* FAttributeTrackingDirectiveBuilder::UnderCondition(UAttributeTrackingConditionBase* TrackingCondition)
{
	if(TrackingResponseAddedForCurrentDescription)
		BeginNewTrackingDescription();
	
	CurrentTrackingDescription->TrackingConditions.Add(TrackingCondition);

	return this;
}

FAttributeTrackingDirectiveBuilder* FAttributeTrackingDirectiveBuilder::AddTrackingResponse(UAttributeTrackingResponseBase* TrackingResponse)
{
	TrackingResponseAddedForCurrentDescription = true;
	CurrentTrackingDescription->TrackingResponses.Add(TrackingResponse);

	return this;
}

void FAttributeTrackingDirectiveBuilder::BeginNewTrackingDescription()
{
	TrackingResponseAddedForCurrentDescription = false;
	const int32 NewIndex = CurrentTrackingDescriptionCollection->TrackingDescriptions.Add(FAttributeTrackingDescription());
	
	CurrentTrackingDescription = &CurrentTrackingDescriptionCollection->TrackingDescriptions[NewIndex];
}

void FAttributeTrackingDirectiveBuilder::BeginNewTrackingDescriptionCollection()
{
	CurrentTrackingDescriptionCollection = &AttributeTrackingMap.Add(CurrentAttribute, FAttributeTrackingDescriptionCollection());

	BeginNewTrackingDescription();
}
