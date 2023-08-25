// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DAbilitySystemLibrary.generated.h"

class UDAttributeMenuWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class DAWN_API UDAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category = "DAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "DAbilitySystemLibrary|WidgetController")
	static UDAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
	
};
