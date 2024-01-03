// "// Copyright 2019 - 2021 AFK Studio"

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "AttributeTrackingCollections.h"
#include "AttributeTrackingDirectiveBase.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class EXAMPLE_API UAttributeTrackingDirectiveBase : public UObject
{
	GENERATED_BODY()

public:
	virtual UAttributeTrackingDirectiveBase* BuildDirective() PURE_VIRTUAL(UAttributeTrackingDirectiveBase::BuildDirective, return nullptr;);
	TMap<FGameplayAttribute, FAttributeTrackingDescriptionCollection> GetAttributeTrackingMap();

protected:

	UPROPERTY()
	TMap<FGameplayAttribute, FAttributeTrackingDescriptionCollection> AttributeTrackingMap;
};
