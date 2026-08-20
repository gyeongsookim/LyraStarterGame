// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * FTemporaryModule
 * 
 * Temporary 플러그인 모듈의 핵심 라이프사이클을 관리하는 모듈 클래스입니다.
 * IModuleInterface를 상속받아 StartupModule / ShutdownModule을 구현합니다.
 */
class FTemporaryModule : public IModuleInterface
{
public:
	/** 플러그인이 엔진에 의해 로드될 때 호출됩니다. */
	virtual void StartupModule() override;

	/** 플러그인이 메모리에서 해제될 때 호출됩니다. */
	virtual void ShutdownModule() override;
};
