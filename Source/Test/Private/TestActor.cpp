// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestActor.h"
#include "Engine/Engine.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	// 로그 및 화면 출력 메시지로 ATestActor 동작 확인
	UE_LOG(LogTemp, Warning, TEXT("[Test Module] ATestActor::BeginPlay() executed successfully!"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 
			7.0f, 
			FColor::Green, 
			TEXT("[Test Module] ATestActor has been spawned and BeginPlay executed!")
		);
	}
}

void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
