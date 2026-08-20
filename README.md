# [7번 과제] 언리얼 모듈과 플러그인 제작 및 연결 가이드

본 프로젝트는 **언리얼 엔진(Unreal Engine)**의 핵심 구조인 **모듈(Module)**과 **플러그인(Plugin)**의 개념을 파악하고, 커스텀 모듈 `Test` 및 커스텀 플러그인 `Temporary`를 수동으로 구축하여 상호 연결 및 C++ 클래스 스폰/참조를 검증한 과제입니다.

---

## 📌 목차
1. [언리얼 모듈과 플러그인 개념](#1-언리얼-모듈과-플러그인-개념)
2. [프로젝트 디렉토리 구조](#2-프로젝트-디렉토리-구조)
3. [1단계: 신규 모듈(Test) 생성 및 구성](#3-1단계-신규-모듈test-생성-및-구성)
4. [2단계: 모듈 연결 및 Target / .uproject 갱신](#4-2단계-모듈-연결-및-target--uproject-갱신)
5. [3단계: 모듈 간 상호작용 (ATestActor & UCharacterData)](#5-3단계-모듈-간-상호작용-atestactor--ucharacterdata)
6. [4단계: 독립 플러그인(Temporary) 구축](#6-4단계-독립-플러그인temporary-구축)
7. [5단계: 도전 기능 (UObject 자식 클래스 & 플러그인 클래스 참조)](#7-5단계-도전-기능-uobject-자식-클래스--플러그인-클래스-참조)
8. [빌드 및 검증 방법](#8-빌드-및-검증-방법)

---

## 1. 언리얼 모듈과 플러그인 개념

| 구분 | 모듈 (Module) | 플러그인 (Plugin) |
| :--- | :--- | :--- |
| **정의** | 소스코드의 최소 컴파일 단위 (DLL 또는 static lib) | 모듈과 콘텐츠(uasset)를 묶은 독립 기능 단위 |
| **빌드 독립성** | 프로젝트의 특정 Target에 포함되어 컴파일 | 프로젝트와 분리하여 타 프로젝트에 손쉽게 이식/재사용 가능 |
| **위치** | `Source/[ModuleName]` | `Plugins/[PluginName]` |
| **설정 파일** | `[ModuleName].Build.cs` | `[PluginName].uplugin` + internal `Build.cs` |

---

## 2. 프로젝트 디렉토리 구조

```text
LyraStarterGame/
├── LyraStarterGame.uproject        # Modules(Test) 및 Plugins(Temporary) 등록
├── Source/
│   ├── LyraStarterGame/            # 주 게임 모듈 (Primary Module)
│   │   ├── LyraStarterGame.Build.cs # Test, Temporary 모듈 종속성 추가
│   │   ├── LyraStarterGameCharacter.h / .cpp # ATestActor, ATemporaryPluginActor, UCharacterData 참조
│   ├── Test/                       # [신규 추가 모듈]
│   │   ├── Test.Build.cs           # Core, CoreUObject, Engine 종속성 정의
│   │   ├── Public/
│   │   │   ├── Test.h             # FTestModule (IModuleInterface)
│   │   │   ├── TestActor.h        # TEST_API 적용 C++ Actor 클래스
│   │   │   └── CharacterData.h    # [도전 기능] TEST_API 적용 UObject 데이터 저장용 클래스
│   │   └── Private/
│   │       ├── Test.cpp           # IMPLEMENT_MODULE(FTestModule, Test)
│   │       ├── TestActor.cpp      # BeginPlay에서 디버그 메시지/로그 출력
│   │       └── CharacterData.cpp  # 데이터 속성 초기화 및 포맷팅 로직
│   ├── LyraStarterGame.Target.cs      # ExtraModuleNames.Add("Test")
│   └── LyraStarterGameEditor.Target.cs# ExtraModuleNames.Add("Test")
└── Plugins/                        # [신규 추가 플러그인]
    └── Temporary/
        ├── Temporary.uplugin       # 플러그인 메타데이터 JSON
        ├── Content/                # 에셋 보관용 폴더
        └── Source/
            └── Temporary/
                ├── Temporary.Build.cs
                ├── Public/
                │   ├── Temporary.h            # FTemporaryModule (IModuleInterface)
                │   └── TemporaryPluginActor.h # TEMPORARY_API 적용 Actor 클래스
                └── Private/
                    ├── Temporary.cpp          # IMPLEMENT_MODULE(FTemporaryModule, Temporary)
                    └── TemporaryPluginActor.cpp
```

---

## 3. 1단계: 신규 모듈(`Test`) 생성 및 구성

### (1) `Test.Build.cs`
`Source/Test/Test.Build.cs` 위치에 작성하여 필수 엔진 모듈을 의존성에 추가합니다.
```csharp
using UnrealBuildTool;
using System.IO;

public class Test : ModuleRules
{
    public Test(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));
    }
}
```

### (2) `Test.h` 및 `Test.cpp`
모듈 라이프사이클을 처리하기 위해 `IModuleInterface`를 구현하고 `IMPLEMENT_MODULE` 매크로를 선언합니다.
```cpp
// Test.cpp
#include "Test.h"
#include "Modules/ModuleManager.h"

void FTestModule::StartupModule()
{
    UE_LOG(LogTemp, Warning, TEXT("[Test Module] StartupModule: Test Module loaded into memory!"));
}

void FTestModule::ShutdownModule()
{
    UE_LOG(LogTemp, Warning, TEXT("[Test Module] ShutdownModule: Test Module unloaded from memory!"));
}

IMPLEMENT_MODULE(FTestModule, Test);
```

---

## 4. 2단계: 모듈 연결 및 Target / .uproject 갱신

1. **Target 파일 수정**:
   `LyraStarterGame.Target.cs` 및 `LyraStarterGameEditor.Target.cs`에 `Test` 모듈을 빌드 대상에 등록합니다.
   ```csharp
   ExtraModuleNames.AddRange(new string[] { "LyraStarterGame", "Test" });
   ```

2. **`.uproject` 파일 수정**:
   `Test` 모듈을 등록하고, 로딩 시점을 `PreDefault`로 설정합니다.
   ```json
   "Modules": [
       {
           "Name": "LyraStarterGame",
           "Type": "Runtime",
           "LoadingPhase": "Default"
       },
       {
           "Name": "Test",
           "Type": "Runtime",
           "LoadingPhase": "PreDefault"
       }
   ]
   ```

---

## 5. 3단계: 모듈 간 상호작용 (`ATestActor` & `UCharacterData`)

### (1) `TEST_API` 매크로를 통한 심볼 내보내기
`Source/Test/Public/TestActor.h`:
```cpp
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

UCLASS()
class TEST_API ATestActor : public AActor
{
    GENERATED_BODY()
public:
    ATestActor();
protected:
    virtual void BeginPlay() override;
};
```

---

## 6. 4단계: 독립 플러그인(`Temporary`) 구축

### (1) `Temporary.uplugin` 메타데이터 작성
`Plugins/Temporary/Temporary.uplugin`:
```json
{
	"FileVersion": 3,
	"Version": 1,
	"VersionName": "1.0",
	"FriendlyName": "Temporary Plugin",
	"Description": "독립적인 C++ 로직과 콘텐츠를 가질 수 있는 커스텀 플러그인 샘플입니다.",
	"Category": "Custom",
	"CanContainContent": true,
	"Modules": [
		{
			"Name": "Temporary",
			"Type": "Runtime",
			"LoadingPhase": "Default"
		}
	]
}
```

### (2) `.uproject` 활성화
`Plugins` 배열에 추가하여 활성화합니다.
```json
"Plugins": [
    {
        "Name": "Temporary",
        "Enabled": true
    }
]
```

---

## 7. 5단계: 도전 기능 (UObject 자식 클래스 & 플러그인 클래스 참조)

### (1) UObject 자식 클래스 (`UCharacterData`) 구현
Test 모듈 내에 데이터 저장용 UObject 클래스를 작성합니다:
```cpp
// Source/Test/Public/CharacterData.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterData.generated.h"

UCLASS(BlueprintType, Blueprintable)
class TEST_API UCharacterData : public UObject
{
	GENERATED_BODY()
public:
	UCharacterData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackPower;

	UFUNCTION(BlueprintCallable)
	FString GetFormattedDataString() const;
};
```

### (2) 캐릭터 클래스(`LyraStarterGameCharacter`)에서 사용 및 화면 출력
```cpp
// LyraStarterGameCharacter.cpp
UCharacterData* CharData = NewObject<UCharacterData>(this);
if (CharData)
{
    FString DataStr = CharData->GetFormattedDataString();
    GEngine->AddOnScreenDebugMessage(-1, 9.0f, FColor::Yellow, FString::Printf(TEXT("[Test Module UObject] %s"), *DataStr));
}
```

---

## 8. 빌드 및 검증 방법

1. Visual Studio 솔루션 또는 C++ 빌드 툴을 사용하여 빌드를 실행합니다:
   ```powershell
   & "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\Build.bat" LyraStarterGameEditor Win64 Development -Project="c:\Unreal\LyraStarterGame\LyraStarterGame.uproject" -WaitMutex
   ```
2. 언리얼 에디터 실행 또는 런타임 플레이 시:
   - 화면 좌상단 디버그 메시지 확인:
     - 🟢 **초록색**: `ATestActor` 스폰 메시지
     - 🩵 **청록색**: `ATemporaryPluginActor` 스폰 메시지
     - 🟡 **노란색**: `UCharacterData` (UObject) 속성 출력 메시지 (`Name: Hero_Antigravity | MaxHP: 150.0 | Speed: 650.0 | Atk: 35`)
