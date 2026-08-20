// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterData.h"

UCharacterData::UCharacterData()
{
	// 초기 속성값 설정
	CharacterName = TEXT("Hero_Antigravity");
	MaxHealth = 150.0f;
	MovementSpeed = 650.0f;
	AttackPower = 35;
}

FString UCharacterData::GetFormattedDataString() const
{
	return FString::Printf(
		TEXT("[UCharacterData] Name: %s | MaxHP: %.1f | Speed: %.1f | Atk: %d"),
		*CharacterName,
		MaxHealth,
		MovementSpeed,
		AttackPower
	);
}
