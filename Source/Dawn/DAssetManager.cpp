// Fill out your copyright notice in the Description page of Project Settings.


#include "DAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "DGameplayTags.h"

UDAssetManager::UDAssetManager()
{
	
}

UDAssetManager& UDAssetManager::Get()
{
	check(GEngine);

	UDAssetManager* DAssetManager = Cast<UDAssetManager>(GEngine->AssetManager);
	return *DAssetManager;
}

void UDAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();

	//Load Native Tags
	FDGameplayTags::InitializeNativeTags();
}
