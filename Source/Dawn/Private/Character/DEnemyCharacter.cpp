// Copyright Aziryel

#include "Character/DEnemyCharacter.h"

#include "DGameplayTags.h"
#include "Components/WidgetComponent.h"
#include "Dawn/Dawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/DAbilitySystemComponent.h"
#include "GAS/DAbilitySystemLibrary.h"
#include "GAS/DAttributeSet.h"
#include "UI/Widget/DUserWidget.h"

ADEnemyCharacter::ADEnemyCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UDAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<UDAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
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

int32 ADEnemyCharacter::GetPlayerLevel()
{
	return Level;
}

void ADEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

	InitializeASC();

	if (UDUserWidget* DawnUserWidget = Cast<UDUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		DawnUserWidget->SetWidgetController(this);
	}
	
	if (AbilitySystemComponent)
	{
		if (const UDAttributeSet* DawnAS = Cast<UDAttributeSet>(Attributes))
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DawnAS->GetHealthAttribute()).AddLambda(
				[this](const FOnAttributeChangeData& Data)
				{
					OnHealthChanged.Broadcast(Data.NewValue);
				}
			);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DawnAS->GetMaxHealthAttribute()).AddLambda(
				[this](const FOnAttributeChangeData& Data)
				{
					OnMaxHealthChanged.Broadcast(Data.NewValue);
				}
			);
			
			AbilitySystemComponent->RegisterGameplayTagEvent(FDGameplayTags::Get().Effect_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
				this,
				&ADEnemyCharacter::HitReactTagChanged
			);
			
		}
	}
	OnHealthChanged.Broadcast(Attributes->GetHealth());
	OnMaxHealthChanged.Broadcast(Attributes->GetMaxHealth());
}

void ADEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void ADEnemyCharacter::InitializeASC()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UDAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

void ADEnemyCharacter::InitializeDefaultAttributes() const
{
	UDAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
