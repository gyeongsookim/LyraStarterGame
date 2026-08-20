// Copyright Epic Games, Inc. All Rights Reserved.

#include "TemporaryPluginActor.h"
#include "Engine/Engine.h"

ATemporaryPluginActor::ATemporaryPluginActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATemporaryPluginActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("[Temporary Plugin] ATemporaryPluginActor::BeginPlay() executed!"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 
			7.0f, 
			FColor::Cyan, 
			TEXT("[Temporary Plugin] ATemporaryPluginActor spawned from Plugin!")
		);
	}
}

void ATemporaryPluginActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
