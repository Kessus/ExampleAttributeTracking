#pragma once

#include "TrackingResponses/AttributeTrackingResponseBase.h"
#include "TrackingConditions/AttributeTrackingConditionBase.h"
#include "AttributeTrackingCollections.generated.h"

USTRUCT()
struct EXAMPLE_API FAttributeTrackingDescription
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UAttributeTrackingResponseBase*> TrackingResponses;
	UPROPERTY()
	TArray<const UAttributeTrackingConditionBase*> TrackingConditions;
};

USTRUCT()
struct EXAMPLE_API FAttributeTrackingDescriptionCollection
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FAttributeTrackingDescription> TrackingDescriptions;
};