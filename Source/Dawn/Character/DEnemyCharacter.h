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
	// Implements the abstract classes from IDInteractable
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
};
