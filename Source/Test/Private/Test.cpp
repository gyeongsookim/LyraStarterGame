// Copyright Epic Games, Inc. All Rights Reserved.

#include "Test.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FTestModule"

void FTestModule::StartupModule()
{
	// Test 모듈 로드 완료 시 로그 출력
	UE_LOG(LogTemp, Warning, TEXT("[Test Module] StartupModule: Test Module loaded into memory!"));
}

void FTestModule::ShutdownModule()
{
	// Test 모듈 언로드 시 로그 출력
	UE_LOG(LogTemp, Warning, TEXT("[Test Module] ShutdownModule: Test Module unloaded from memory!"));
}

#undef LOCTEXT_NAMESPACE

// 언리얼 모듈 시스템에 Test 모듈 등록
IMPLEMENT_MODULE(FTestModule, Test);
