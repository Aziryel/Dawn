// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/DWidgetController.h"
#include "DAttributeMenuWidgetController.generated.h"

struct FGameplayAttribute;
struct FGameplayTag;
class UAttributeInfo;
struct FDAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FDAttributeInfo&, Info);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DAWN_API UDAttributeMenuWidgetController : public UDWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;	
};
