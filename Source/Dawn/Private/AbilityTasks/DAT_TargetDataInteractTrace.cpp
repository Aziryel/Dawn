// Copyright Aziryel


#include "AbilityTasks/DAT_TargetDataInteractTrace.h"

UDAT_TargetDataInteractTrace* UDAT_TargetDataInteractTrace::CreateTargetDataInteractTrace(
	UGameplayAbility* OwningAbility)
{
	UDAT_TargetDataInteractTrace* MyObj = NewAbilityTask<UDAT_TargetDataInteractTrace>(OwningAbility);
	return MyObj;
}
