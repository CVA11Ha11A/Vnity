#pragma once
#include "VObject.h"


class VUI : public VObject
{   // UI의 좌상단 포지션은 해당 개체의 포지션 (Player같은건 중앙이 포지션임)
    // TODO : UI 현재 사용불가(24.10.18) 씬이동시 객체 소멸자에서 Heap메모리 손상일어남 구조변경 필요

private:
    vector<VUI*>    m_vecChildUI;       // UI가 가지고 있는 UI
    VUI*            m_pParentUI;        // 자신의 상위 UI(게임오브젝트 계층구조 같은느낌)    
    Vector2         m_vFinalPos;        // 최종위치

    bool            m_bCamAffected;     // 카메라의 영향을 받는지(렌더될경우)
    bool            m_bMouseOn;         // UI위에 마우스가 존재하는지
    bool            m_bLbtnDown;        // UI에 왼쪽버튼이 눌린적이 있는지

public:
    Vector2 GetFinalPos()   { return m_vFinalPos;  }
    VUI* GetParent()        { return m_pParentUI; }
    bool IsMouseOn()        { return m_bMouseOn; }
    bool IsLbtnDown()       { return m_bLbtnDown; }

    void AddChild(VUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
    const vector<VUI*>& GetChildUI() { return m_vecChildUI; }



public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void FinalUpdate();
    virtual void Render(HDC _dc);
    
private:
    void Update_Child();
    void FinalUpdate_Child();
    void Render_Child(HDC _dc);

    void MouseOnCheck();


public:
    virtual void MouseOn();             // UI위에 마우스가 올라올경우호출되는 함수

    virtual void MouseLbtnDown();       // UI에서 마우스 좌클릭시 호출될 함수
    virtual void MouseLbtnUp();         // UI에서 마우스 좌클릭땔 경우 호출될 함수
    virtual void MouseLbtnClicked();    // UI에서 마우스 클릭이 감지 될경우(내부에서 Donw, UP이 되어야함)
    

    virtual VUI* Clone() = 0;

public:
    VUI(bool _bCamAffedcted);
    VUI(const VUI& _origin);
    virtual ~VUI();

    friend class VUIManager;
};

