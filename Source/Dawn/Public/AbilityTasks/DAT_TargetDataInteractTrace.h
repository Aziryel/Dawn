// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "DAT_TargetDataInteractTrace.generated.h"

/**
 * 
 */
UCLASS()
class DAWN_API UDAT_TargetDataInteractTrace : public UAbilityTask
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "TargetDataInteractTrace", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UDAT_TargetDataInteractTrace* CreateTargetDataInteractTrace(UGameplayAbility* OwningAbility);
	
};
