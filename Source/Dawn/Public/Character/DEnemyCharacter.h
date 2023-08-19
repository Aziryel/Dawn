// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "DCharacterBase.h"
#include "DEnemyCharacter.generated.h"

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
	
	/** End Interface */
	virtual int32 GetPlayerLevel() override;
	/** Combat Interface */
	
	/** End Combat Interface */

protected:
	virtual void BeginPlay() override;
	virtual void InitializeASC() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Default")
	int32 Level = 1;

};
