// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TemporaryPluginActor.generated.h"

/**
 * ATemporaryPluginActor
 * 
 * [도전 기능] Temporary 플러그인 모듈에 포함된 C++ Actor 클래스입니다.
 * TEMPORARY_API 매크로를 통해 모듈 외부로 심볼을 노출하여,
 * 다른 모듈이나 메인 게임 모듈에서 직접 참조 및 스폰할 수 있도록 구현되어 있습니다.
 */
UCLASS()
class TEMPORARY_API ATemporaryPluginActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATemporaryPluginActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
