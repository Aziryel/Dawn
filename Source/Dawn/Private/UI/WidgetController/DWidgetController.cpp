// Copyright Aziryel


#include "UI/WidgetController/DWidgetController.h"

void UDWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UDWidgetController::BroadcastInitialValues()
{
	
}

void UDWidgetController::BindCallbacksToDependencies()
{
	
}
