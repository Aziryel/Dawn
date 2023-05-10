// Copyright Aziryel


#include "DWeaponBase.h"

#include "Abilities/Tasks/AbilityTask_NetworkSyncPoint.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Dawn/Character/DPlayerCharacter.h"

ADWeaponBase::ADWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(RootComponent);
	SetRootComponent(WeaponMesh);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PickupArea = CreateDefaultSubobject<UCapsuleComponent>("PickupSphere");
	PickupArea->SetupAttachment(RootComponent);
	PickupArea->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AbilitySystemComponent = CreateDefaultSubobject<UDAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>("PickupWidget");
	PickupWidget->SetupAttachment(RootComponent);
	PickupWidget->SetVisibility(false);
}

void ADWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	// Only do this on the Server
	if (true/*HasAuthority()*/)
	{
		PickupArea->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		PickupArea->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		PickupArea->SetCollisionResponseToChannel(COLLISION_ABILITY, ECR_Overlap);
		PickupArea->SetCollisionResponseToChannel(COLLISION_INTERACTABLE, ECR_Overlap);
		PickupArea->OnComponentBeginOverlap.AddDynamic(this, &ADWeaponBase::OnCapsuleOverlap);
		PickupArea->OnComponentEndOverlap.AddDynamic(this, &ADWeaponBase::OnCapsuleEndOverlap);
	}
}

void ADWeaponBase::OnCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ADWeaponBase::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ADWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ADWeaponBase::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	//return IDInteractable::IsAvailableForInteraction_Implementation(InteractionComponent);
	if (InteractionComponent == PickupArea)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ADWeaponBase::GetPreInteractSyncType_Implementation(bool& bShouldSync, EAbilityTaskNetSyncType& Type,
	UPrimitiveComponent* InteractionComponent) const
{
	//IDInteractable::GetPreInteractSyncType_Implementation(bShouldSync, Type, InteractionComponent);
	if (InteractionComponent == PickupArea)
	{
		bShouldSync = false;
		Type = EAbilityTaskNetSyncType::OnlyClientWait;
	}
	else
	{
		bShouldSync = false;
		Type = EAbilityTaskNetSyncType::BothWait;
	}
}

float ADWeaponBase::GetInteractionDuration_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	//return IDInteractable::GetInteractionDuration_Implementation(InteractionComponent);
	if (InteractionComponent == PickupArea)
	{
		return InteractionDuration;
	}
	else
	{
		return 0.0f;
	}
}

UAbilitySystemComponent* ADWeaponBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ADWeaponBase::ShowPickupWidget(bool bShowWidget)
{
	if (PickupWidget)
	{
		PickupWidget->SetVisibility(bShowWidget);
	}
}

