// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/DCharacterMovementComponent.h"
#include "Character/DCharacterBase.h"

float UDCharacterMovementComponent::GetMaxSpeed() const
{
	ADCharacterBase* Owner = Cast<ADCharacterBase>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s() Has no Owner!"), *FString(__FUNCTION__));
	}

	if (!Owner->IsAlive())
	{
		return 0.0f;
	}
	
	return Owner->GetMovementSpeed();
}
