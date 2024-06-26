// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "DCharacterBase.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "GAS/Data/CharacterClassInfo.h"
#include "DEnemyCharacter.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class DAWN_API ADEnemyCharacter : public ADCharacterBase
{
	GENERATED_BODY()
public:
	ADEnemyCharacter(const FObjectInitializer& ObjectInitializer);

	
	/** Implements the abstract classes from IDInteractable */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	
	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
	/** End Combat Interface */

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;

protected:
	virtual void BeginPlay() override;
	virtual void InitializeASC() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Default")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Default")
	ECharacterClass CharacterClass = ECharacterClass::Fighter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

};
