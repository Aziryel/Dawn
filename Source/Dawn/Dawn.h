// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define ACTOR_ROLE_FSTRING *(FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"), true)->GetNameStringByValue(GetLocalRole()))
#define GET_ACTOR_ROLE_FSTRING(Actor) *(FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"), true)->GetNameStringByValue(Actor->GetLocalRole()))

#define ECC_ABILITY						ECollisionChannel::ECC_GameTraceChannel1
#define ECC_PROJECTILE					ECollisionChannel::ECC_GameTraceChannel2
#define ECC_ABILITYOVERLAPPROJECTILE		ECollisionChannel::ECC_GameTraceChannel3
#define ECC_PICKUP						ECollisionChannel::ECC_GameTraceChannel4
#define ECC_INTERACTABLE					ECollisionChannel::ECC_GameTraceChannel5

#define CUSTOM_DEPTH_WHITE 250