// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterData.generated.h"

/**
 * UCharacterData
 * 
 * [도전 기능 구현] UObject를 상속받은 캐릭터 데이터 저장용 C++ 클래스입니다.
 * Test 모듈에 수록되어 있으며, TEST_API 매크로를 이용해 타 모듈로 심볼을 내보냅니다.
 * 캐릭터의 기본 속성(이름, 체력, 이동속도, 공격력) 및 포맷 문자열 반환 기능을 제공합니다.
 */
UCLASS(BlueprintType, Blueprintable)
class TEST_API UCharacterData : public UObject
{
	GENERATED_BODY()

public:
	// 기본 생성자 - 기본 데이터 속성 초기화
	UCharacterData();

	/** 캐릭터 이름 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	FString CharacterName;

	/** 최대 체력 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float MaxHealth;

	/** 이동 속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float MovementSpeed;

	/** 기본 공격력 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	int32 AttackPower;

	/** 속성 데이터를 화면 및 로그 출력용 FString 형태로 포맷팅하여 반환하는 함수 */
	UFUNCTION(BlueprintCallable, Category = "Character Data")
	FString GetFormattedDataString() const;
};
