// Copyright Aziryel


#include "DWeaponBase.h"

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

	// Only do this on the Server
	if (HasAuthority())
	{
		PickupArea->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		PickupArea->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		PickupArea->OnComponentBeginOverlap.AddDynamic(this, &ADWeaponBase::OnCapsuleOverlap);
		PickupArea->OnComponentEndOverlap.AddDynamic(this, &ADWeaponBase::OnCapsuleEndOverlap);
	}
}

void ADWeaponBase::OnCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADPlayerCharacter* PlayerCharacter = Cast<ADPlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		PlayerCharacter->SetOverlappingWeapon(this);
	}
}

void ADWeaponBase::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ADPlayerCharacter* PlayerCharacter = Cast<ADPlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		PlayerCharacter->SetOverlappingWeapon(nullptr);
	}
}

void ADWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

