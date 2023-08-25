// Copyright Aziryel


#include "UI/WidgetController/DAttributeMenuWidgetController.h"
#include "GAS/DAttributeSet.h"
#include "GAS/Data/AttributeInfo.h"

void UDAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UDAttributeSet* AS = CastChecked<UDAttributeSet>(AttributeSet);
	check(AttributeInfo);
	
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
		);
	}
}

void UDAttributeMenuWidgetController::BroadcastInitialValues()
{
	UDAttributeSet* AS = CastChecked<UDAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& Pair: AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UDAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	//Find the Attribute using the tag stored in the key assigned in the DAttributeSet TMap
	//and using that tag to search for the attribute in the data asset using the function FindAttributeInfoForTag
	FDAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	//We can use the numerical value using the Value and the AttributeSet
	//and then assign it to the AttributeValue in the DataAsset to broadcast the value to the widget blueprint
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
