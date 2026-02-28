# 🚀 Shooter Sam (Unreal Engine 5 C++)

**Udemy의 'Unreal Engine 5 C++ Developer' 과정을 기반으로 제작된 3인칭 슈팅(TPS) 액션 게임 프로젝트입니다.**
단순한 슈팅 구현을 넘어, C++ Delegate를 활용한 이벤트 기반 아키텍처를 설계하고 클래스 상속을 통한 효율적인 캐릭터 관리 시스템을 구축하는 데 집중했습니다.

---

## 📺 Project Showcase
- **Demonstration Video:** [https://youtu.be/WSG8CsqDGkk]

---

## 🛠 Core Technical Implementations (C++)

### 🎯 Key System: Event-Driven Boss Raid
이 프로젝트는 매 프레임 상태를 확인하는 Polling 방식 대신, 특정 사건이 발생했을 때만 신호를 보내는 **Observer 패턴**을 C++ Delegate로 구현했습니다.

#### **1. C++ Multicast Delegate 활용 (`OnBossDied`)**
- **정의:** `DECLARE_DYNAMIC_MULTICAST_DELEGATE`를 사용하여 보스 캐릭터가 사망하는 순간 레벨에 신호를 보낼 수 있는 '발신기'를 구축했습니다.
- **이점:** 레벨 블루프린트에서 보스들의 상태를 `Tick`으로 계속 검사할 필요 없이, 사망 시점에만 단 한 번 이벤트를 수신하므로 CPU 자원을 획기적으로 절약했습니다.

#### **2. 클래스 상속 및 속성 필터링 (Object-Oriented Design)**
- **구조:** 부모 클래스인 `AShooterSamCharacter`에 `bIsBoss` 플래그를 추가하여 주인공 캐릭터와 일반 적, 보스 캐릭터가 동일한 코드 베이스를 공유하도록 설계했습니다.
- **로직:** `OnDamageTaken` 함수 내부에서 `if (bIsBoss)` 조건문을 통해 보스로 설정된 액터만 `OnBossDied.Broadcast()`를 호출하도록 필터링하여 시스템의 범용성을 확보했습니다.

#### **3. 레벨 블루프린트 연동 및 탈출 기믹**
- **사망 카운트 로직:** 레벨 시작 시 `Get All Actors of Class`를 통해 보스들을 탐색하고, 각 보스의 사망 이벤트를 `Bind` 하여 실시간 사망자 수를 카운트하는 로직을 구현했습니다.
- **상호작용:** 카운트가 목표치(3)에 도달하면 `Mover` 컴포넌트의 `SetShouldMove`를 활성화하여 엘리베이터 승천 시퀀스를 트리거합니다.

---

## 💡 Problem Solving (Troubleshooting)

**Problem 1: 블루프린트만으로는 복잡해지는 이벤트 통신 구조.**
- **Solution:** 레벨 내 여러 보스의 상태를 실시간으로 추적하는 로직을 블루프린트의 `Tick`이나 복잡한 `Loop`로 구현하는 대신, **Visual Studio(C++)에서 Delegate를 선언**하여 해결했습니다. C++에서 시스템의 뼈대(이벤트 발송)를 잡고 블루프린트에서 이를 호출하는 방식을 채택함으로써, 로직이 훨씬 단순해지고 에러 수정이 용이해졌습니다.

**Problem 2: 엘리베이터 상승 시 유리 천장과의 물리적 충돌 및 캐릭터 끼임.**
- **Solution:** 천장을 파괴하거나 복잡한 물리 계산을 도입하는 대신, **'No Collision' 설정을 활용한 눈속임 기믹**으로 손쉽게 해결했습니다. 유리 천장의 콜리전을 제거하여 캐릭터와 엘리베이터가 부드럽게 통과하도록 설정함으로써, 시각적 효과는 유지하면서도 물리 엔진의 오작동으로 인한 캐릭터 떨림 현상을 완벽히 방지했습니다.

**Problem 3: 캐릭터 이동 시 발걸음이 지면에 미끄러지는 어색한 현상.**
- **Solution:** 애니메이션과 실제 이동 속도 사이의 불일치(Foot Sliding)를 해결하기 위해 캐릭터 무브먼트 컴포넌트의 파라미터를 미세 조정했습니다. 애니메이션의 보폭에 맞춰 **`MaxWalkSpeed`를 최적화**함으로써, 별도의 복잡한 IK 설정 없이도 지면을 단단히 딛고 이동하는 듯한 자연스러운 움직임을 구현했습니다.

---

## 📦 Assets & Resources
- **Logic:** 슈팅 판정(Line Trace), 체력 시스템, 이벤트 델리게이트 등 모든 핵심 로직은 C++로 구현되었습니다.
- **Environment Assets:** Udemy 강의에서 제공하는 *Simple Shooter* 에셋 팩을 활용하였습니다.
  - *Character Models, Gun Meshes, SFX, VFX* 등

---

## 🔧 Tech Stack
- **Engine:** Unreal Engine 5 (5.4+)
- **Language:** C++ (Visual Studio 2022)
- **Version Control:** Git, GitHub
