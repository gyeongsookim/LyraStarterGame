// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * FTestModule
 * 
 * Test 모듈의 주 모듈 인터페이스 클래스입니다.
 * 모듈이 메모리에 로드 및 언로드될 때의 렌더링/초기화 라이프사이클을 관리합니다.
 */
class FTestModule : public IModuleInterface
{
public:
	/** 모듈 로드 시 실행되는 초기화 함수 */
	virtual void StartupModule() override;

	/** 모듈 언로드 시 실행되는 해제 함수 */
	virtual void ShutdownModule() override;
};
