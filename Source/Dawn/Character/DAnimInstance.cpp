// Copyright Aziryel


#include "DAnimInstance.h"
#include "DPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UDAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerCharacter = Cast<ADPlayerCharacter>(TryGetPawnOwner());
}

void UDAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<ADPlayerCharacter>(TryGetPawnOwner());
	}
	if (!PlayerCharacter) return;

	FVector Velocity = PlayerCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = PlayerCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = PlayerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
}
