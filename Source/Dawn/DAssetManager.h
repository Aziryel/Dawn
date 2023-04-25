#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DAssetManager.generated.h"


UCLASS()
class DAWN_API UDAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	UDAssetManager();

	//Returns the AssetManager singleton object
	static UDAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
