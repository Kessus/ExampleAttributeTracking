// "// Copyright 2019 - 2021 AFK Studio"
#include "TrackingResponses/AttributeTrackingResponseBase.h"

float UAttributeTrackingResponseBase::GetLastRegisteredValue() const
{
	return LastRegisteredValue;
}

bool UAttributeTrackingResponseBase::ResponseHasBegun() const
{
	return HasBegun;
}

void UAttributeTrackingResponseBase::Begin(float ChangeAmount)
{
	LastRegisteredValue = ChangeAmount;
	HasBegun = true;
}

void UAttributeTrackingResponseBase::Update(float ChangeAmount)
{
	LastRegisteredValue = ChangeAmount;
}

void UAttributeTrackingResponseBase::End()
{
	HasBegun = false;
}
