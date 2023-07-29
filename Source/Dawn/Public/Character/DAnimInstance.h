// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DAWN_API UDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:

	UPROPERTY(BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class ADPlayerCharacter* PlayerCharacter;

	UPROPERTY(BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	UPROPERTY(BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating;
	
};
