// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dawn/UI/DPlayerStatsWidget.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class DAWN_API ADPlayerController : public APlayerController
{
	GENERATED_BODY()

	ADPlayerController();
	virtual void OnRep_PlayerState() override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UIWidgets")
	TSubclassOf<UDPlayerStatsWidget> UIPlayerStatsClass;
	UPROPERTY(BlueprintReadWrite, Category = "UI Widgets")
	UDPlayerStatsWidget* UIPlayerStats;

	UFUNCTION()
	void TogglePlayerStats();

	UFUNCTION()
	void CreateHUD();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> KeyboardMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> GamepadMappingContext;
};
