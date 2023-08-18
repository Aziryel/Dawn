// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/DCharacterMovementComponent.h"
#include "Character/DCharacterBase.h"
#include "GAS/DAttributeSet.h"

float UDCharacterMovementComponent::GetMaxSpeed() const
{
	ADCharacterBase* Owner = Cast<ADCharacterBase>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s() Has no Owner!"), *FString(__FUNCTION__));
	}

	if (!Owner->IsAlive())
	{
		return 0.f;
	}
	if (Owner->GetAttributeSet())
	{
		return Owner->GetAttributeSet()->GetMovementSpeed();
	}

	return 0.f;
}
