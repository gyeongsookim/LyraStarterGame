// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

/**
 * ATestActor
 * 
 * Test 모듈에 정의된 C++ Actor 클래스입니다.
 * TEST_API 매크로를 사용하여 주 모듈(LyraStarterGame) 등 외부 모듈에서 
 * 이 클래스의 심볼에 접근하고 인스턴스를 스폰할 수 있도록 동적 링크(DLL Export)를 지원합니다.
 */
UCLASS()
class TEST_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// 기본 생성자
	ATestActor();

protected:	
	// 게임 시작 시 또는 인스턴스 생성 시 호출되는 함수
	virtual void BeginPlay() override;

public:	
	// 매 프레임 호출되는 틱 함수
	virtual void Tick(float DeltaTime) override;
};
