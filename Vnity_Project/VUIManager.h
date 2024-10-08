#pragma once

class VUI;


class VUIManager
{
	SINGLETON(VUIManager);

private:
	VUI* m_pFocusedUI;		// 포커싱된 UI

public:
	void Update();

	void SetFocusedUI(VUI* _pUI);

private:
	VUI* GetFocusedUI();

	// 부모 UI 내에서 실제로 타겟팅 된 UI를 찾아서 반환하는 함수
	VUI* GetTargetedUI(VUI* _pParentUI);

};

