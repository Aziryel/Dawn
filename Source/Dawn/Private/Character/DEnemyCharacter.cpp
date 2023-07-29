// Copyright Aziryel

#include "Character/DEnemyCharacter.h"
#include "Dawn/Dawn.h"
#include "GAS/DAbilitySystemComponent.h"
#include "GAS/DAttributeSet.h"

ADEnemyCharacter::ADEnemyCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UDAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	Attributes = CreateDefaultSubobject<UDAttributeSet>("AttributeSet");
}

void ADEnemyCharacter::HighlightActor()
{
	Super::HighlightActor();
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_WHITE);
}

void ADEnemyCharacter::UnHighlightActor()
{
	Super::UnHighlightActor();
	GetMesh()->SetCustomDepthStencilValue(0);
	GetMesh()->SetRenderCustomDepth(false);
}