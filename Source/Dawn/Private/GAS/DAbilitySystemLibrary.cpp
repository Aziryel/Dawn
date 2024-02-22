// Copyright Aziryel


#include "GAS/DAbilitySystemLibrary.h"

#include "GameModes/DGameModeBase.h"
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

void UDAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	ADGameModeBase* DawnGameMode = Cast<ADGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (DawnGameMode == nullptr) return;

	UCharacterClassInfo* CharacterClassInfo = DawnGameMode->GetCharacterClassInfo();
	if (!CharacterClassInfo)
	{
		GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Purple,
		FString::Printf(TEXT("Character Class Info is not set on the Game Mode Blueprint!!!"))
		);
	}

	AActor* AvatarActor = ASC->GetAvatarActor();
	
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}
