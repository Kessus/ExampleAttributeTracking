// "// Copyright 2019 - 2021 AFK Studio"

#pragma once

#include "CoreMinimal.h"
#include "AttributeTrackingCollections.h"
#include "Components/ActorComponent.h"
#include "AttributeTrackingDatabase.h"
#include "TrackingDirectives/AttributeTrackingDirectiveBase.h"
#include "AttributeTrackingManager.generated.h"

class UExampleAbilitySystemComponent;

UCLASS(BlueprintType)
class EXAMPLE_API UAttributeTrackingManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttributeTrackingManager();

	UAttributeTrackingManager* Init(UExampleAbilitySystemComponent* AbilitySystem);

	void RegisterAttributeChangeForTracking(FGameplayAttribute Attribute, float ChangeAmount, FAttributeTrackingMetadata Metadata = FAttributeTrackingMetadata()) const;
	//In the future we might add non-attribute related values for tracking here. 

	bool HasAttributeChangedRecently(FGameplayAttribute Attribute, const UAttributeTrackingConditionBase* Condition) const;
	bool HasAttributeChangedRecently(FGameplayAttribute Attribute, const TArray<const UAttributeTrackingConditionBase*> Conditions) const;
	float GetRecentAttributeChangeAmount(FGameplayAttribute Attribute, const UAttributeTrackingConditionBase* Condition) const;
	float GetRecentAttributeChangeAmount(FGameplayAttribute Attribute, const TArray<const UAttributeTrackingConditionBase*> Conditions) const;
	
	void ApplyAttributeTrackingDirective(UAttributeTrackingDirectiveBase* Directive);

protected:
	void InitializeTrackingForAttribute(FGameplayAttribute AttributeToTrack);
	
	UPROPERTY()
	UAttributeTrackingDatabase* AttributeTrackingDatabase;

	UPROPERTY()
	UExampleAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	TMap<FGameplayAttribute, FAttributeTrackingDescriptionCollection> TrackingDescriptionsForAttribute;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float AttributeTrackingRefreshPeriod = 0.1f;

	FTimerDelegate AttributeTrackingRefreshDelegate;
	FTimerHandle AttributeTrackingTimerHandle;

	void RefreshAttributeTracking();
};
