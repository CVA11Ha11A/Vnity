#pragma once
#include "VObject.h"


class VUI : public VObject
{   // UI�� �»�� �������� �ش� ��ü�� ������ (Player������ �߾��� ��������)
    // TODO : UI ���� ���Ұ�(24.10.18) ���̵��� ��ü �Ҹ��ڿ��� Heap�޸� �ջ��Ͼ �������� �ʿ�

private:
    vector<VUI*>    m_vecChildUI;       // UI�� ������ �ִ� UI
    VUI*            m_pParentUI;        // �ڽ��� ���� UI(���ӿ�����Ʈ �������� ��������)    
    Vector2         m_vFinalPos;        // ������ġ

    bool            m_bCamAffected;     // ī�޶��� ������ �޴���(�����ɰ��)
    bool            m_bMouseOn;         // UI���� ���콺�� �����ϴ���
    bool            m_bLbtnDown;        // UI�� ���ʹ�ư�� �������� �ִ���

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
    virtual void MouseOn();             // UI���� ���콺�� �ö�ð��ȣ��Ǵ� �Լ�

    virtual void MouseLbtnDown();       // UI���� ���콺 ��Ŭ���� ȣ��� �Լ�
    virtual void MouseLbtnUp();         // UI���� ���콺 ��Ŭ���� ��� ȣ��� �Լ�
    virtual void MouseLbtnClicked();    // UI���� ���콺 Ŭ���� ���� �ɰ��(���ο��� Donw, UP�� �Ǿ����)
    

    virtual VUI* Clone() = 0;

public:
    VUI(bool _bCamAffedcted);
    VUI(const VUI& _origin);
    virtual ~VUI();

    friend class VUIManager;
};

