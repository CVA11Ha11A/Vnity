# Vnity
WinApi Unity 모방을 목표로 학습용도로 제작중인 프로젝트입니다.

참조<br/>
https://www.youtube.com/watch?v=dlFr-OnHlWU&list=PL4SIC1d_ab-ZLg4TvAO5R4nqlJTyJXsPK<br/>
해당 영상을 참조하여서 기본 베이스를 공부 및 제작 하였습니다.

상시 업데이트예정이며 해당 프로그램으로 게임도 만들어보며 계속 업데이트 할 예정입니다.

# 업데이트
<details>
  <summary><b>라이프사이클</b></summary>
현재사이클<br/><br/>
ManagerUpdate(Input, Time, Camera)<br/>
SceneUpdate(Objcet Awake)<br/>
SceneUpdate(Objcet Start)<br/>
SceneUpdate(Objcet Update)<br/>
CoroutineWaitForSecond(Unity의 yield return WaitForSecond)<br/>
CoroutineWaitForOneFrame(Unity의 yield return WaitForSecond)<br/>
Collistion, Rigidbody<br/>
UI<br/>
Render<br/>
CoroutineSetting(지연 코루틴 재 등록)
Event(CreateObject ,Destroy, SceneChange))<br/>
</details>

<details>
  <summary>Object</summary>
  1. DonDestroy 추가<br/>
  &nbsp;a. 씬이동시 파괴 안되도록 제작<br/>
    b. 내부 DieEvent로는 오브젝트가 파괴<br/>
</details>

<details>
  <summary>Coroutine</summary>
  1. VObject를 상속받은 객체가 사용가능<br/>
    a. 호출방식 StartCoroutin<현재 객체>(함수, this(객체의 포인터))<br/>
  2. return 방식<br/>
    a. (Unity) yield return new WaitForSecond(float _f) -> (Vnity) new WaitForSecond(float _f)<br/>
    b. 유니티처럼 함수 탈출지점부터 시작하지않음 초기부터 시작하기에 switch, if 분기점으로 나누어주어야함<br/>
  3. 관리방식<br/>
    a. 엔진 내부에서 코루틴을 관리해주도록 제작<br/>
    b. new 한 WaitForSecond, WaitForOneFrame 같은것은 CoroutineManager에서 자동적으로 관리해주기때문에 신경쓰지 않아도되도록 제작<br/>
    
</details>

<details>
  <summary><b>TODO</b></summary>
  코루틴
</details>
