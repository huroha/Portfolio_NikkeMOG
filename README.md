# Portfolio_MOG

WinAPI 기반 2D 액션 슈팅 게임 프로젝트입니다. 

## 프로젝트 개요

### 게임 장르
- **액션 슈팅 게임** (뱀파이어 서바이벌류)
- **2D 탑다운 뷰**
- **멀티 캐릭터 시스템**

### 주요 특징
- 스킬업 시스템 및 패시브 능력
- 보스전 및 적 스포너 시스템
- 게임 에디터 기능

- **언어**: C++
- **API**: WinAPI (Windows API)
- **IDE**: Visual Studio 2022
- **플랫폼**: Windows (x64)

## 주요 시스템

### 게임플레이 시스템
- **Player**: 캐릭터 선택 및 조작
- **Enemy**: 다양한 적 AI 및 스포너
- **Boss**: 보스전 시스템
- **Missile**: 다양한 무기/탄환 시스템 (Basic, Thunder, Trace, Guided 등)
- **Item**: 아이템 드롭 및 자동 수집

### 전투 시스템
- **Attack States**: 다양한 공격 패턴
- **State Machine**: 캐릭터 및 적 상태 관리
- **Collision**: 정밀한 충돌 감지
- **Effect**: 시각적 이펙트 및 사운드

### UI/UX 시스템
- **Weapon UI**: 무기 선택 인터페이스
- **Passive UI**: 패시브 스킬 관리
- **Count UI**: 스탯 업그레이드 시스템
- **HP/Gauge**: 체력 및 게이지 표시

### 엔진 시스템
- **Asset Manager**: 리소스 관리
- **Animation**: 스프라이트 애니메이션
- **Sound**: 사운드 및 BGM 시스템
- **Camera**: 카메라 제어
- **Collision**: 충돌 감지 시스템

### 적 시스템
- **Enemy1**: 기본 적 유닛
- **Boss**: 보스 몬스터
- **Spawner**: 적 생성 시스템

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

## 개발 일지 Notion Link
https://decisive-bell-c02.notion.site/SHFITUP-Nikke-MOG-ac979f76ada449ec8287344a2774c9cb?pvs=74

[[게임 시연 유튜브 링크]](https://youtu.be/xpcwNJXNOjk)
