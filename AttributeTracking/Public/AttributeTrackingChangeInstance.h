#pragma once
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "AttributeTrackingChangeInstance.generated.h"

USTRUCT()
struct EXAMPLE_API FAttributeTrackingMetadata
{
	GENERATED_BODY()
    
	FAttributeTrackingMetadata() {}
	FAttributeTrackingMetadata(const FOnAttributeChangeData& ChangeData)
	{
		EffectSpec = ChangeData.GEModData->EffectSpec;
	}
    
	//This is being copied over, perhaps in the future we might need to find another way of accessing it (like a handle)
	UPROPERTY()
	FGameplayEffectSpec EffectSpec;
};


USTRUCT()
struct EXAMPLE_API FAttributeTrackingChangeInstance
{
	GENERATED_BODY();
	
	FAttributeTrackingChangeInstance(): ChangeAmount(0.0f){}
	FAttributeTrackingChangeInstance(float ChangeAmount, FAttributeTrackingMetadata Metadata, float ExpirationTimeSeconds) : ChangeAmount(ChangeAmount), Metadata(Metadata)
	{
		TrackingExpirationTime = FDateTime::Now() + FTimespan(0,0, ExpirationTimeSeconds);
		TrackingStartTime = FDateTime::Now();
	}
	
	float ChangeAmount;
	FDateTime TrackingStartTime;
	FDateTime TrackingExpirationTime;
	
	UPROPERTY()
	FAttributeTrackingMetadata Metadata;
};

USTRUCT()
struct EXAMPLE_API FAttributeTrackingChangeInstanceCollection
{
	GENERATED_BODY();
	
	UPROPERTY()
	TArray<FAttributeTrackingChangeInstance> ChangeInstances;
};