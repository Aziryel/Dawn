// Copyright Aziryel


#include "DCombatComponent.h"

UDCombatComponent::UDCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UDCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UDCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

