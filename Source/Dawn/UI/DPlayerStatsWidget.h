// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DUserWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "DPlayerStatsWidget.generated.h"

/**
 * 
 */
UCLASS()
class DAWN_API UDPlayerStatsWidget : public UDUserWidget
{
	GENERATED_BODY()

public:
	UDPlayerStatsWidget();

	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URichTextBlock* StrText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URichTextBlock* DexText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URichTextBlock* VitText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URichTextBlock* IntText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URichTextBlock* WisText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* StrButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* DexButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* VitButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* IntButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* WisButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HealthText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ManaText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ManaBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* StatsBorder;

	UFUNCTION()
	void UpdateText(UTextBlock* TextToModify, float NewValue);
	UFUNCTION()
	void UpdateProgressBar(UProgressBar* BarToModify, float NewValue, float MaxValue);
	UFUNCTION()
	void UpdateStats(URichTextBlock* TextToModify, float NewValue);

	UFUNCTION()
	void ModifyStrength();
	UFUNCTION()
	void ModifyDexterity();
	UFUNCTION()
	void ModifyVitality();
	UFUNCTION()
	void ModifyIntelligence();
	UFUNCTION()
	void ModifyWisdom();
	
};
