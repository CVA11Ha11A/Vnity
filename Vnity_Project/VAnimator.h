#pragma once


class VObject;
class VAnimation;
class VTexture;

class VAnimator
{	// 애니메이션을 관리해줄 개체

private:
	map<wstring, VAnimation*>	m_mapAnim;		// 애니메이션을 담아둘 Map
	VAnimation*					m_pCurAnim;		// 현재 재생중인 Animation
	VObject*					m_pOwner;		// 해당 컴포넌트를 가지고 있는 개체의 포인터
	bool						m_bIsLoop;		// 애니메이션을 반복재생 할 것인지

public:
	VObject* GetObj() 	{ return m_pOwner; }

public:
	/// <summary>
	/// 애니메이션 생성하는 함수
	/// </summary>
	/// <param name="_strName"> : 생성할 애니메이션 이름</param>
	/// <param name="_pTex"> : 사용할 텍스쳐</param>
	/// <param name="_vLT"> : 애니메이션에 사용할 텍스쳐의 좌상단(어디부터 할지)</param>
	/// <param name="_SliceSize"> : 얼만큼자를것인지</param>
	/// <param name="_vStep"> : 얼만큼의 간격을 띄워야하는지</param>
	/// <param name="_iFrameCount"> : 몇 frame인지</param>
	void CreateAnimation(const wstring& _strName, VTexture* _pTex , Vector2 _vLT,
		Vector2 _vSliceSize, Vector2 _vStep, float _fDuration, UINT _iFrameCount);
	void LoadAnimation(const wstring& _strRelativePath);
	VAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bIsLoop);


	void Update();
	void FinalUpdate();
	void Render(HDC _dc);



public:
	VAnimator();
	~VAnimator();

	friend class VObject;	

};

