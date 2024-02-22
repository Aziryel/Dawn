// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DGameModeBase.generated.h"

class UCharacterClassInfo;

UCLASS()
class DAWN_API ADGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Character Class Defaults")
	UCharacterClassInfo* GetCharacterClassInfo() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
