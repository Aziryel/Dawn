// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DHUD.generated.h"

class UDAttributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
class UDUserWidget;
class UOverlayWidgetController;
struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class DAWN_API ADHUD : public AHUD
{
	GENERATED_BODY()
public:

	//To create the widget from the player controller in blueprint
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDUserWidget> OverlayWidget;
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UDAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
protected:
	
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UDAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
		
};
