// Copyright Aziryel


#include "DGAInteractScan.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "Dawn/Character/DPlayerCharacter.h"
#include "Dawn/Interfaces/DInteractable.h"
#include "Dawn/Weapon/DWeaponBase.h"

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
}

void UDGAInteractScan::LoseInteractTarget()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->SetOverlappingWeapon(nullptr);
	}
}

void UDGAInteractScan::AfterInputPress(float TimeWaited)
{
	UE_LOG(LogTemp, Warning, TEXT("Press for Interaction! Time: %f"), TimeWaited);
}

