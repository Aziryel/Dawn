// Copyright Aziryel


#include "UI/HUD/DHUD.h"
#include "UI/Widget/DUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/DAttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* ADHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController != nullptr) return OverlayWidgetController;
	OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
	OverlayWidgetController->SetWidgetControllerParams(WCParams);
	OverlayWidgetController->BindCallbacksToDependencies();

	return OverlayWidgetController;
}

UDAttributeMenuWidgetController* ADHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController != nullptr) return AttributeMenuWidgetController;
	AttributeMenuWidgetController = NewObject<UDAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
	AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
	AttributeMenuWidgetController->BindCallbacksToDependencies();

	return AttributeMenuWidgetController;
}

void ADHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_DHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_DHUD"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UDUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}
