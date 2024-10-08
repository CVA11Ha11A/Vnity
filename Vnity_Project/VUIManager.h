#pragma once

class VUI;


class VUIManager
{
	SINGLETON(VUIManager);

private:
	VUI* m_pFocusedUI;		// ��Ŀ�̵� UI

public:
	void Update();

	void SetFocusedUI(VUI* _pUI);

private:
	VUI* GetFocusedUI();

	// �θ� UI ������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�ϴ� �Լ�
	VUI* GetTargetedUI(VUI* _pParentUI);

};

