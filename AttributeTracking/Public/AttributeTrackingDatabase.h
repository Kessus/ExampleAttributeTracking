// "// Copyright 2019 - 2021 AFK Studio"

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "TrackingConditions/AttributeTrackingConditionBase.h"
#include "Object.h"
#include "AttributeTrackingDatabase.generated.h"

/**
 * 
 */
UCLASS()
class EREBOS_API UAttributeTrackingDatabase : public UObject
{
	GENERATED_BODY()

public:
	UAttributeTrackingDatabase* Init(FTimerManager& TimerManager);

	void RegisterAttributeChangeForTracking(FGameplayAttribute Attribute, float ChangeAmount, FAttributeTrackingMetadata Metadata = FAttributeTrackingMetadata());

	bool ChangeInstanceFitsAllConditions(const FAttributeTrackingChangeInstance& ChangeInstance, const TArray<const UAttributeTrackingConditionBase*> Conditions) const;
	bool HasAttributeChangedRecently(FGameplayAttribute Attribute, const TArray<const UAttributeTrackingConditionBase*> Conditions);
	float GetRecentAttributeChangeAmount(FGameplayAttribute Attribute, const TArray<const UAttributeTrackingConditionBase*> Conditions);

protected:
	static bool IsChangeInstanceExpired(const FAttributeTrackingChangeInstance& ChangeInstance);
	void RemoveExpiredChangeInstances();

	UPROPERTY()
	TMap<FGameplayAttribute,FAttributeTrackingChangeInstanceCollection> ChangeInstancesForAttribute;

	FTimerHandle InstanceExpiryCheckTimerHandle;
	FTimerDelegate InstanceExpiryCheckDelegate;
	float InstanceExpirationTimeSeconds = 10.0f;
};
