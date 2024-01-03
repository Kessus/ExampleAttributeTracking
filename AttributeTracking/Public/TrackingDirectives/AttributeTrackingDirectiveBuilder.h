// "// Copyright 2019 - 2021 AFK Studio"

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeTrackingCollections.h"
#include "AttributeTrackingDirectiveBuilder.generated.h"

/**
 * 
 */
USTRUCT()
struct EXAMPLE_API FAttributeTrackingDirectiveBuilder
{
	GENERATED_BODY()

public:
	TMap<FGameplayAttribute, FAttributeTrackingDescriptionCollection> ToTrackingDescriptionMap();
	FAttributeTrackingDirectiveBuilder* ForAttribute(FGameplayAttribute Attribute);
	FAttributeTrackingDirectiveBuilder* UnderCondition(UAttributeTrackingConditionBase* TrackingCondition);
	FAttributeTrackingDirectiveBuilder* AddTrackingResponse(UAttributeTrackingResponseBase* TrackingResponse);

protected:
	void BeginNewTrackingDescription();
	void BeginNewTrackingDescriptionCollection();
	
	FGameplayAttribute CurrentAttribute;
	FAttributeTrackingDescription* CurrentTrackingDescription;
	FAttributeTrackingDescriptionCollection* CurrentTrackingDescriptionCollection;
	
	bool TrackingResponseAddedForCurrentDescription = false;
	
	UPROPERTY()
	TMap<FGameplayAttribute, FAttributeTrackingDescriptionCollection> AttributeTrackingMap;
};
