// Copyright Aziryel


#include "DEnemyCharacter.h"

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
