// Copyright Aziryel


#include "GAS/DAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerState/DPlayerState.h"
#include "UI/HUD/DHUD.h"
#include "UI/WidgetController/DWidgetController.h"

UOverlayWidgetController* UDAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ADHUD* DHUD = Cast<ADHUD>(PC->GetHUD()))
		{
			ADPlayerState* PS = PC->GetPlayerState<ADPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSetBase();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return DHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UDAttributeMenuWidgetController* UDAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ADHUD* DHUD = Cast<ADHUD>(PC->GetHUD()))
		{
			ADPlayerState* PS = PC->GetPlayerState<ADPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSetBase();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return DHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
