// "// Copyright 2019 - 2021 AFK Studio"


#include "TrackingResponses/AttributeTrackingTagResponse.h"

#include "Kismet/KismetSystemLibrary.h"

UAttributeTrackingTagResponse* UAttributeTrackingTagResponse::Init(FGameplayTag TagToSetAsResponse,	UExampleAbilitySystemComponent* AbilitySystemComponent)
{
	ResponseTag = TagToSetAsResponse;
	AbilitySystem = AbilitySystemComponent;

	return this;
}

void UAttributeTrackingTagResponse::Begin(float ChangeAmount)
{
	Super::Begin(ChangeAmount);
	
	AbilitySystem->AddReplicatedGameplayTag(ResponseTag);
}

void UAttributeTrackingTagResponse::End()
{
	AbilitySystem->RemoveReplicatedGameplayTag(ResponseTag);

	Super::End();
}
