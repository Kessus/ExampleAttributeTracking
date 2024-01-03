// "// Copyright 2019 - 2021 AFK Studio"


#include "AttributeTrackingManager.h"
#include "ExampleAbilitySystemComponent.h"


// Sets default values for this component's properties
UAttributeTrackingManager::UAttributeTrackingManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UAttributeTrackingManager* UAttributeTrackingManager::Init(UExampleAbilitySystemComponent* AbilitySystem)
{
	AttributeTrackingDatabase = NewObject<UAttributeTrackingDatabase>(this, "AttributeTrackingDatabase");

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	AttributeTrackingDatabase->Init(TimerManager);

	AbilitySystemComponent = AbilitySystem;

	AttributeTrackingRefreshDelegate.BindUObject(this, &UAttributeTrackingManager::RefreshAttributeTracking);
	TimerManager.SetTimer(AttributeTrackingTimerHandle, AttributeTrackingRefreshDelegate, AttributeTrackingRefreshPeriod, true);

	return this;
}

void UAttributeTrackingManager::ApplyAttributeTrackingDirective(UAttributeTrackingDirectiveBase* Directive)
{
	TMap<FGameplayAttribute, FAttributeTrackingDescriptionCollection> AttributeTrackingMap = Directive->GetAttributeTrackingMap();
	for(TTuple<FGameplayAttribute, FAttributeTrackingDescriptionCollection> DirectiveBehavioursForAttribute : AttributeTrackingMap)
	{
		FGameplayAttribute CurrentAttribute = DirectiveBehavioursForAttribute.Key;
		if(!TrackingDescriptionsForAttribute.Contains(CurrentAttribute))
			InitializeTrackingForAttribute(CurrentAttribute);
		
		FAttributeTrackingDescriptionCollection* TrackingDescriptionsForCurrentAttribute = TrackingDescriptionsForAttribute.Find(CurrentAttribute);
		TrackingDescriptionsForCurrentAttribute->TrackingDescriptions.Append(DirectiveBehavioursForAttribute.Value.TrackingDescriptions);
	}
}

void UAttributeTrackingManager::InitializeTrackingForAttribute(FGameplayAttribute AttributeToTrack)
{
	TrackingDescriptionsForAttribute.Add(AttributeToTrack);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeToTrack).AddLambda([this, AttributeToTrack](const FOnAttributeChangeData& ValueChangeData)
	{
		const float ChangeAmount = ValueChangeData.NewValue - ValueChangeData.OldValue;
		FAttributeTrackingMetadata ChangeMetadata;
		if(ValueChangeData.GEModData)
			ChangeMetadata = FAttributeTrackingMetadata(ValueChangeData);
				
		RegisterAttributeChangeForTracking(AttributeToTrack, ChangeAmount, ChangeMetadata);
	});
}

void UAttributeTrackingManager::RefreshAttributeTracking()
{
	TArray<FGameplayAttribute> TrackedAttributes;
	TrackingDescriptionsForAttribute.GetKeys(TrackedAttributes);
	
	for(FGameplayAttribute TrackedAttribute : TrackedAttributes)
	{
		FAttributeTrackingDescriptionCollection* TrackingBehavioursForCurrentAttribute = TrackingDescriptionsForAttribute.Find(TrackedAttribute);
		for(FAttributeTrackingDescription& TrackingDescription : TrackingBehavioursForCurrentAttribute->TrackingDescriptions)
		{
			const float ChangeAmount = GetRecentAttributeChangeAmount(TrackedAttribute, TrackingDescription.TrackingConditions);
			if(ChangeAmount != 0.0f)
			{
				for(UAttributeTrackingResponseBase* TrackingResponse : TrackingDescription.TrackingResponses)
				{
					if(!TrackingResponse->ResponseHasBegun())
						TrackingResponse->Begin(ChangeAmount);
					else if(TrackingResponse->GetLastRegisteredValue() != ChangeAmount)
						TrackingResponse->Update(ChangeAmount);
				}
			}
			else
			{
				for(UAttributeTrackingResponseBase* TrackingResponse : TrackingDescription.TrackingResponses)
					if(TrackingResponse->ResponseHasBegun())
						TrackingResponse->End();
			}
		}
	}
}

void UAttributeTrackingManager::RegisterAttributeChangeForTracking(FGameplayAttribute Attribute, float ChangeAmount, FAttributeTrackingMetadata Metadata) const
{
	AttributeTrackingDatabase->RegisterAttributeChangeForTracking(Attribute, ChangeAmount, Metadata);
}

bool UAttributeTrackingManager::HasAttributeChangedRecently(FGameplayAttribute Attribute, const UAttributeTrackingConditionBase* Condition) const
{
	TArray<const UAttributeTrackingConditionBase*> Conditions;
	Conditions.Add(Condition);
	return HasAttributeChangedRecently(Attribute, Conditions);
}

bool UAttributeTrackingManager::HasAttributeChangedRecently(FGameplayAttribute Attribute, const TArray<const UAttributeTrackingConditionBase*> Conditions) const
{
	return AttributeTrackingDatabase->HasAttributeChangedRecently(Attribute, Conditions);
}

float UAttributeTrackingManager::GetRecentAttributeChangeAmount(FGameplayAttribute Attribute, const UAttributeTrackingConditionBase* Condition) const
{
	TArray<const UAttributeTrackingConditionBase*> Conditions;
	Conditions.Add(Condition);
	return GetRecentAttributeChangeAmount(Attribute, Conditions);
}

float UAttributeTrackingManager::GetRecentAttributeChangeAmount(FGameplayAttribute Attribute, const TArray<const UAttributeTrackingConditionBase*> Conditions) const
{
	return AttributeTrackingDatabase->GetRecentAttributeChangeAmount(Attribute, Conditions);
}
