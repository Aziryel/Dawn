// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Dawn/Character/DPlayerCharacter.h"
#include "Dawn/PlayerState/DPlayerState.h"


ADPlayerController::ADPlayerController()
{
	bReplicates = true;
}

void ADPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* EISubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(EISubsystem)

	if (KeyboardMappingContext && GamepadMappingContext)
	{
		EISubsystem->AddMappingContext(KeyboardMappingContext, 0);
		EISubsystem->AddMappingContext(GamepadMappingContext, 0);
	}
}

void ADPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	CreateHUD();
}

void ADPlayerController::TogglePlayerStats()
{
	/*if (!UIPlayerStats || UIPlayerStats->GetName() == "None")
	{
		UIPlayerStats = CreateWidget<UDPlayerStatsWidget>(this, UIPlayerStatsClass);
		UIPlayerStats->AddToViewport();
		UIPlayerStats->SetVisibility(ESlateVisibility::Collapsed);
		UE_LOG(LogTemp, Warning, TEXT("Create Widget!"));
	}*/
	if (UIPlayerStats->StatsBorder && UIPlayerStats->StatsBorder->GetVisibility() == ESlateVisibility::Collapsed)
	{
		UIPlayerStats->StatsBorder->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this, UIPlayerStats);
		SetShowMouseCursor(true);
		SetIgnoreLookInput(true);
		SetIgnoreMoveInput(true);
		UIPlayerStats->SetFocus();
	}
	else
	{
		UIPlayerStats->StatsBorder->SetVisibility(ESlateVisibility::Collapsed);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
		SetShowMouseCursor(false);
		SetIgnoreLookInput(false);
		SetIgnoreMoveInput(false);
	}
}

void ADPlayerController::CreateHUD()
{
	if (!IsLocalPlayerController())
	{
		return;
	}

	ADPlayerState* PS = GetPlayerState<ADPlayerState>();
	if (!PS)
	{
		return;
	}
	
	if (!UIPlayerStats || UIPlayerStats->GetName() == "None")
	{
		UIPlayerStats = CreateWidget<UDPlayerStatsWidget>(this, UIPlayerStatsClass);
		UIPlayerStats->AddToViewport();
		UIPlayerStats->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		UIPlayerStats->UpdateText(UIPlayerStats->HealthText, PS->AttributeSet->GetHealth());
		UIPlayerStats->UpdateProgressBar(UIPlayerStats->HealthBar, PS->AttributeSet->GetHealth(), PS->AttributeSet->GetMaxHealth());
		UIPlayerStats->UpdateText(UIPlayerStats->ManaText, PS->AttributeSet->GetMana());
		UIPlayerStats->UpdateProgressBar(UIPlayerStats->ManaBar, PS->AttributeSet->GetMana(), PS->AttributeSet->GetMaxMana());
		// Update Stats
		UIPlayerStats->UpdateStats(UIPlayerStats->StrText, PS->AttributeSet->GetStrength());
		UIPlayerStats->UpdateStats(UIPlayerStats->DexText, PS->AttributeSet->GetDexterity());
		UIPlayerStats->UpdateStats(UIPlayerStats->VitText, PS->AttributeSet->GetVitality());
		UIPlayerStats->UpdateStats(UIPlayerStats->IntText, PS->AttributeSet->GetIntelligence());
		UIPlayerStats->UpdateStats(UIPlayerStats->WisText, PS->AttributeSet->GetWisdom());
		UE_LOG(LogTemp, Warning, TEXT("Create Widget!"));
	}
}


