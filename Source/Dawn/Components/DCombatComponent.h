// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DCombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAWN_API UDCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDCombatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
