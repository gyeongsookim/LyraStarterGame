// Copyright Epic Games, Inc. All Rights Reserved.

#include "Temporary.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FTemporaryModule"

void FTemporaryModule::StartupModule()
{
	// 플러그인 로드 시 디버그 로그
	UE_LOG(LogTemp, Warning, TEXT("[Temporary Plugin] StartupModule: Temporary Plugin Module has been loaded."));
}

void FTemporaryModule::ShutdownModule()
{
	// 플러그인 언로드 시 디버그 로그
	UE_LOG(LogTemp, Warning, TEXT("[Temporary Plugin] ShutdownModule: Temporary Plugin Module has been unloaded."));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTemporaryModule, Temporary)
