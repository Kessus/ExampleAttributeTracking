// "// Copyright 2019 - 2021 AFK Studio"


#include "AttributeTracking/AttributeTrackingDatabase.h"

#include "ErebosBasicAttributeSet.h"

UAttributeTrackingDatabase* UAttributeTrackingDatabase::Init(FTimerManager& TimerManager)
{
	InstanceExpiryCheckDelegate.BindUObject(this, &UAttributeTrackingDatabase::RemoveExpiredChangeInstances);
	TimerManager.SetTimer(InstanceExpiryCheckTimerHandle, InstanceExpiryCheckDelegate, InstanceExpirationTimeSeconds, true, InstanceExpirationTimeSeconds);
	
	return this;
}

void UAttributeTrackingDatabase::RegisterAttributeChangeForTracking(FGameplayAttribute Attribute, float ChangeAmount, FAttributeTrackingMetadata Metadata)
{
	if(ChangeAmount == 0.0f)
		return;
	
	FAttributeTrackingChangeInstance ChangeInstance = FAttributeTrackingChangeInstance(ChangeAmount, Metadata, InstanceExpirationTimeSeconds);
	if(ChangeInstancesForAttribute.Contains(Attribute))
	{
		ChangeInstancesForAttribute[Attribute].ChangeInstances.Add(ChangeInstance);
	}
	else
	{
		FAttributeTrackingChangeInstanceCollection NewChangeInstanceCollection;
		NewChangeInstanceCollection.ChangeInstances.Add(ChangeInstance);
		ChangeInstancesForAttribute.Add(Attribute, NewChangeInstanceCollection);
	}
}

bool UAttributeTrackingDatabase::ChangeInstanceFitsAllConditions(const FAttributeTrackingChangeInstance& ChangeInstance, const TArray<const UAttributeTrackingConditionBase*> Conditions) const
{
	bool FitsAllConditions = true;
	for(const UAttributeTrackingConditionBase* Condition : Conditions)
	{
		if(!Condition->ChangeFitsCondition(ChangeInstance))
		{
			FitsAllConditions = false;
			break;
		}
	}

	return FitsAllConditions;
}

bool UAttributeTrackingDatabase::HasAttributeChangedRecently(FGameplayAttribute Attribute, const TArray<const UAttributeTrackingConditionBase*> Conditions)
{
	checkf(Attribute.IsValid(), TEXT("Invalid attribute supplied for attribute tracking query."));

	if(!ChangeInstancesForAttribute.Contains(Attribute))
		return false;
	
	const FAttributeTrackingChangeInstanceCollection& ChangeInstanceCollection = ChangeInstancesForAttribute[Attribute];
	
	for(const FAttributeTrackingChangeInstance& ChangeInstance : ChangeInstanceCollection.ChangeInstances)
	{
		if(IsChangeInstanceExpired(ChangeInstance))
			continue;
		
		if(ChangeInstanceFitsAllConditions(ChangeInstance, Conditions))
			return true;
	}
	
	return false;
}

float UAttributeTrackingDatabase::GetRecentAttributeChangeAmount(FGameplayAttribute Attribute, const TArray<const UAttributeTrackingConditionBase*> Conditions)
{
	checkf(Attribute.IsValid(), TEXT("Invalid attribute supplied for attribute tracking query."));

	if(!ChangeInstancesForAttribute.Contains(Attribute))
		return 0.0f;
	
	const FAttributeTrackingChangeInstanceCollection& ChangeInstanceCollection = ChangeInstancesForAttribute[Attribute];
	float AttributeChangeAmount = 0.0f;
	
	for(auto ChangeInstance : ChangeInstanceCollection.ChangeInstances)
	{
		if(IsChangeInstanceExpired(ChangeInstance))
			continue;
		
		if(ChangeInstanceFitsAllConditions(ChangeInstance, Conditions))
			AttributeChangeAmount += ChangeInstance.ChangeAmount;
	}

	return AttributeChangeAmount;
}

bool UAttributeTrackingDatabase::IsChangeInstanceExpired(const FAttributeTrackingChangeInstance& ChangeInstance)
{	
	const FDateTime CurrentTime = FDateTime::Now();
	return CurrentTime >= ChangeInstance.TrackingExpirationTime;
}

void UAttributeTrackingDatabase::RemoveExpiredChangeInstances()
{
	for(TTuple<FGameplayAttribute, FAttributeTrackingChangeInstanceCollection> ChangeInstances : ChangeInstancesForAttribute)
	{
		FAttributeTrackingChangeInstanceCollection& ChangeInstancesForCurrentAttribute = ChangeInstances.Value;
		const int CurrentChangeCount = ChangeInstancesForCurrentAttribute.ChangeInstances.Num();

		for(int i = CurrentChangeCount - 1; i <= 0 ; i--)
		{
			const FAttributeTrackingChangeInstance& ChangeInstance = ChangeInstancesForCurrentAttribute.ChangeInstances[i];
			if(IsChangeInstanceExpired(ChangeInstance))
			{
				ChangeInstancesForCurrentAttribute.ChangeInstances.RemoveAt(i);
			}
		}
	}
}