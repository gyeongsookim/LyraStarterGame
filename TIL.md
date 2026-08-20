# 📝 Today I Learned (TIL): 언리얼 엔진 모듈 & 플러그인 심화 및 트러블슈팅

---

## 💡 핵심 학습 내용 (Core Concepts)

### 1. 동적 링크 매크로와 심볼 내보내기 (`MODULE_API`)
- **개념**: 언리얼 엔진은 각 모듈을 독립된 동적 링크 라이브러리(DLL)로 빌드합니다.
- **원리**: Windows C++ DLL 환경에서는 DLL 외부로 클래스나 함수를 노출하기 위해 `__declspec(dllexport)` 및 `__declspec(dllimport)` 키워드가 필요합니다. 언리얼 엔진은 이를 자동화하기 위해 모듈명에 대응하는 `[MODULENAME]_API` 매크로(예: `TEST_API`, `TEMPORARY_API`)를 언리얼 빌드 툴(UBT)이 자동으로 생성합니다.
- **트러블슈팅**: `TEST_API` 매크로 없이 헤더만 `#include`하고 다른 모듈에서 클래스를 인스턴스화하거나 멤버 함수를 호출하면, 링커 레벨에서 **LNK2019 / LNK2001 (unresolved external symbol)** 오류가 발생합니다.

---

### 2. 모듈 로딩 단계 (`LoadingPhase`)
.uproject 또는 .uplugin 파일의 모듈 항목에서 `LoadingPhase`는 엔진 시작 라이프사이클 중 해당 모듈이 메모리에 언제 로드될지 결정합니다.

| LoadingPhase | 로딩 시점 | 주요 용도 |
| :--- | :--- | :--- |
| **`EarliestPossible`** | 엔진 라이브러리 로드 극초기 | 최하위 플랫폼/시스템 플러그인 |
| **`PreDefault`** | 기본 게임 모듈 로드 직전 | 코어 프레임워크, 셰이더, 전역 매니저 |
| **`Default`** | 일반적인 게임 모듈 로드 시점 | 대부분의 런타임 게임 모듈 및 플러그인 |
| **`PostEngineInit`** | 엔진 초기화 완결 직후 | UI, 툴, 사용자 정의 에디터 확장 |

> 💡 **본 실습 적용**: 과제 요구사항에 따라 `Test` 모듈의 `LoadingPhase`를 `PreDefault`로 설정하여 주 게임 모듈(`LyraStarterGame`)보다 먼저 로드되도록 구성했습니다.

---

### 3. Build.cs 종속성 분리 (Public vs Private Dependencies)

```csharp
// Test.Build.cs
PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
PrivateDependencyModuleNames.AddRange(new string[] { });
```

- **`PublicDependencyModuleNames`**:
  - 내 모듈의 **Public 헤더(.h)** 파일에서 참조하는 외부 모듈.
  - 내 모듈을 의존성으로 추가하는 제3의 모듈에게도 해당 외부 모듈 헤더 포함 관계가 **전이(Propagate)**됩니다.
- **`PrivateDependencyModuleNames`**:
  - 내 모듈의 **Private 소스(.cpp)** 파일 내에서만 숨겨서 참조하는 외부 모듈.
  - 헤더 전이가 발생하지 않아 컴파일 시간에 이점이 있습니다.

---

### 4. 프로젝트(Project) vs 플러그인(Plugin) 차이점 정리

1. **독립성 (Portability)**:
   - **프로젝트**: 독자적으로 빌드 및 실행 바이너리(.exe)를 생성할 수 있는 루트 관리 단위.
   - **플러그인**: 독립 실행은 불가능하며, 프로젝트에 종속되어 기능을 확장하는 부품(Component). 다른 프로젝트의 `Plugins/` 폴더로 복사하는 것만으로 손쉽게 이식(Portable) 가능.
2. **구성 요소**:
   - 플러그인은 C++ 소스코드(`Source/`) 뿐만 아니라 블루프린트, 텍스처, 사운드 등 고유한 콘텐츠(`Content/`)를 포함할 수 있으며, `.uplugin` 파일로 메타데이터와 활성화 여부를 관리합니다.

---

## 🛠️ 개발 중 발생했던 문제 및 해결 방법 (Troubleshooting)

### Q1. 타 모듈의 클래스를 SpawnActor하려고 할 때 컴파일 오류 발생
- **원인**: 주 게임 모듈(`LyraStarterGame.Build.cs`)에 새로 만든 `Test` 모듈과 `Temporary` 플러그인 모듈 의존성을 추가하지 않아서 발생.
- **해결**: `LyraStarterGame.Build.cs`의 `PublicDependencyModuleNames`에 `"Test"`, `"Temporary"`를 추가하여 C++ 이중 포함 헤더 경로와 라이브러리 링크를 정상화함.

### Q2. `Target.cs` 파일 미갱신 시 빌드 누락 현상
- **원인**: `.uproject`에만 모듈을 등록하고 `Target.cs`의 `ExtraModuleNames`에 추가하지 않을 경우, 풋프린트 빌드 타겟에 모듈이 포함되지 않거나 패키징 시 모듈 바이너리가 빌드되지 않는 현상 발생.
- **해결**: `LyraStarterGame.Target.cs` 및 `LyraStarterGameEditor.Target.cs` 두 타겟 파일 모두에 `ExtraModuleNames.AddRange(new string[] { "LyraStarterGame", "Test" });` 구문을 명확하게 작성함.

---

## 🎯 결론 및 성찰
모듈화(Modularization) 구조 설계를 익힘으로써 단순 소스코드의 나열을 넘어, 대규모 게임 개발 시 각 시스템을 계층별로 분리하고 빌드 시간을 단축하며 코드 간 결합도를 낮추는 아키텍처 감각을 습득했습니다.
