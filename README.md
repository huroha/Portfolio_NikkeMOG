# Portfolio_MOG

WinAPI 기반 2D 액션 슈팅 게임 프로젝트입니다. NIKKE 스타일의 캐릭터들과 다양한 무기 시스템을 특징으로 합니다.

## 프로젝트 개요

### 게임 장르
- **액션 슈팅 게임** (뱀파이어 서바이벌류)
- **2D 탑다운 뷰**
- **멀티 캐릭터 시스템**

### 주요 특징
- 다양한 NIKKE 캐릭터들 (Modernia, Lapunzel, Snow, Crown, Killo 등)
- 실시간 미사일/탄막 시스템
- 스킬업 시스템 및 패시브 능력
- 보스전 및 적 스포너 시스템
- 게임 에디터 기능

## 기술 스택

- **언어**: C++
- **API**: WinAPI (Windows API)
- **IDE**: Visual Studio 2022
- **플랫폼**: Windows (x64)

## 주요 시스템

### 🎮 게임플레이 시스템
- **Player**: 캐릭터 선택 및 조작
- **Enemy**: 다양한 적 AI 및 스포너
- **Boss**: 보스전 시스템
- **Missile**: 다양한 무기/탄환 시스템 (Basic, Thunder, Trace, Guided 등)
- **Item**: 아이템 드롭 및 자동 수집

### 🎯 전투 시스템
- **Attack States**: 다양한 공격 패턴
- **State Machine**: 캐릭터 및 적 상태 관리
- **Collision**: 정밀한 충돌 감지
- **Effect**: 시각적 이펙트 및 사운드

### 🎨 UI/UX 시스템
- **Weapon UI**: 무기 선택 인터페이스
- **Passive UI**: 패시브 스킬 관리
- **Count UI**: 스탯 업그레이드 시스템
- **HP/Gauge**: 체력 및 게이지 표시

### 🔧 엔진 시스템
- **Asset Manager**: 리소스 관리
- **Animation**: 스프라이트 애니메이션
- **Sound**: 사운드 및 BGM 시스템
- **Camera**: 카메라 제어
- **Collision**: 충돌 감지 시스템

## 캐릭터 시스템

### 플레이어블 캐릭터
- **Modernia**: 강력한 화력 특화
- **Lapunzel**: 유도 무기 특화  
- **Snow**: 범위 공격 특화
- **Crown**: 방어형 캐릭터
- **Killo**: 근거리 전투 특화

### 적 시스템
- **Enemy1**: 기본 적 유닛
- **Boss**: 강력한 보스 몬스터
- **Spawner**: 적 생성 시스템

## 빌드 방법

1. Visual Studio 2022에서 `Portfolio_MOG.vcxproj` 열기
2. 솔루션 구성을 **Release** 또는 **Debug**로 설정
3. 플랫폼을 **x64**로 설정
4. **빌드 → 솔루션 빌드** (Ctrl+Shift+B)
5. 실행 파일은 `x64/Release/` 또는 `x64/Debug/` 폴더에 생성

## 게임 조작법

- **이동**: WASD 또는 방향키
- **공격**: 자동 공격 (타겟 기반)
- **스킬**: 스페이스바
- **일시정지**: ESC

## 프로젝트 구조

```
Portfolio_MOG/
├── 📁 Core System
│   ├── CEngine.cpp/.h          # 메인 엔진
│   ├── CAssetMgr.cpp/.h        # 리소스 관리
│   ├── CLevelMgr.cpp/.h        # 레벨 관리
│   └── CTimeMgr.cpp/.h         # 시간 관리
├── 📁 Game Objects
│   ├── CPlayer.cpp/.h          # 플레이어
│   ├── CEnemy.cpp/.h           # 적 시스템
│   ├── CBoss.cpp/.h            # 보스
│   └── CMissile.cpp/.h         # 미사일 시스템
├── 📁 Characters
│   ├── CModernia.cpp/.h        # 모더니아
│   ├── CLapunzel.cpp/.h        # 라푼젤
│   ├── CSnow.cpp/.h            # 스노우
│   └── 기타 캐릭터들...
├── 📁 Combat System
│   ├── CAttackState.cpp/.h     # 공격 상태
│   ├── CStateMachine.cpp/.h    # 상태 머신
│   └── CCollisionMgr.cpp/.h    # 충돌 관리
└── 📁 UI System
    ├── CUI.cpp/.h              # UI 기본 클래스
    ├── CWeapon_UI.cpp/.h       # 무기 UI
    └── CPassive_UI.cpp/.h      # 패시브 UI
```

## 개발 환경 요구사항

- **OS**: Windows 10/11 (x64)
- **IDE**: Visual Studio 2019/2022
- **SDK**: Windows SDK 10.0 이상
- **Runtime**: Visual C++ Redistributable

## 라이선스

이 프로젝트는 포트폴리오 목적으로 제작되었습니다.

## 개발자 노트

이 프로젝트는 WinAPI를 활용한 2D 게임 엔진 개발과 게임플레이 시스템 구현에 중점을 두었습니다. 특히 다음과 같은 기술적 도전을 포함합니다:

- 효율적인 탄막 처리 시스템
- 유연한 상태 머신 설계
- 확장 가능한 캐릭터 시스템
- 최적화된 충돌 감지 알고리즘
