// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dawn/UI/DPlayerStatsWidget.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

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
};
