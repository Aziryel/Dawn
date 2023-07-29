// Copyright Aziryel

#include "GAS/DGAInteractScan.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "Character/DPlayerCharacter.h"
#include "Interfaces/DInteractable.h"
#include "Weapon/DWeaponBase.h"

void UDGAInteractScan::WaitForConfirmation()
{
	FHitResult TargetHitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(CurrentTracedTarget, 0);
	TSoftObjectPtr<IDInteractable> Interactable = TargetHitResult.GetActor();
	float Duration = Interactable->GetInteractionDuration_Implementation(TargetHitResult.GetComponent());

	ADWeaponBase* InteractableWeapon = Cast<ADWeaponBase>(TargetHitResult.GetActor());
	if (InteractableWeapon)
	{
		if (!PlayerCharacter)
		{
			PlayerCharacter = Cast<ADPlayerCharacter>(GetOwningActorFromActorInfo());
			UE_LOG(LogTemp, Warning, TEXT("Only cast to player character"));
		}
		if (PlayerCharacter)
		{
			PlayerCharacter->SetOverlappingWeapon(InteractableWeapon);
		}
	}

	if (IDInteractable* InteractableTarget = Cast<IDInteractable>(TargetHitResult.GetActor()))
	{
		InteractableTarget->HighlightActor();
	}
}

void UDGAInteractScan::LoseInteractTarget()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->SetOverlappingWeapon(nullptr);
	}
	FHitResult TargetHitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(CurrentTracedTarget, 0);
	
	if (ADCharacterBase* InteractableTarget = Cast<ADCharacterBase>(TargetHitResult.GetActor()))
	{
		InteractableTarget->UnHighlightActor();
	}
}

void UDGAInteractScan::AfterInputPress(float TimeWaited)
{
	UE_LOG(LogTemp, Warning, TEXT("Press for Interaction! Time: %f"), TimeWaited);
}

