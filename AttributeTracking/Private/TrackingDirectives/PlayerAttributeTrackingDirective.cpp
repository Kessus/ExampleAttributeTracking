// "// Copyright 2019 - 2021 AFK Studio"


#include "TrackingDirectives/PlayerAttributeTrackingDirective.h"
#include "AttributeTrackingDirectiveBuilder.h"
#include "ExampleBasicAttributeSet.h"
#include "TrackingConditions/BasicAttributeTrackingCondition.h"
#include "TrackingResponses/AttributeTrackingTagResponse.h"

UPlayerAttributeTrackingDirective* UPlayerAttributeTrackingDirective::Init(UExampleAbilitySystemComponent* AbilitySystemComponent)
{
	AbilitySystem = AbilitySystemComponent;

	return this;
}

UAttributeTrackingDirectiveBase* UPlayerAttributeTrackingDirective::BuildDirective()
{
	FAttributeTrackingDirectiveBuilder DirectiveBuilder = FAttributeTrackingDirectiveBuilder();
	AttributeTrackingMap = DirectiveBuilder
	.ForAttribute(UExampleBasicAttributeSet::GetStaminaAttribute())
		->UnderCondition(NewObject<UBasicAttributeTrackingCondition>(this)->Init(2.0f, EAttributeChangeType::Negative))
			->AddTrackingResponse(NewObject<UAttributeTrackingTagResponse>()->Init(FGameplayTag::RequestGameplayTag("AttributeTracking.StaminaUsed.RestrictRegeneration"), AbilitySystem))
			
	->ToTrackingDescriptionMap();
	
	return this;
}
