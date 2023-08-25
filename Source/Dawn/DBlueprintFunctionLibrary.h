// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DBlueprintFunctionLibrary.generated.h"


struct FGameplayAbilityTargetDataHandle;

UCLASS()
class DAWN_API UDBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* FGameplayAbilityTargetDataHandle
	*/
	UFUNCTION(BlueprintCallable, Category = "Ability|TargetData")
	static void ClearTargetData(UPARAM(ref) FGameplayAbilityTargetDataHandle& TargetData);
	
};
