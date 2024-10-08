#pragma once
#include "VGlobal.h"

class VAnimator;
class VTexture;

struct tAnimFrm
{
	Vector2 vLT;		// 자신 프레임텍스쳐의 좌상단
	Vector2 vSlice;		// 자를 사이즈 영역
	Vector2 vOffset;	// 해당 프레임의 offset
	float	fDuration;	// 애니메이션 재생 시간

};


class VAnimation
{


private:
	wstring				m_strName;
	VAnimator*			m_pAnimator;
	VTexture*			m_pTex;		// Animation이 사용하는 TexturePointer
	vector<tAnimFrm>	m_vecFrm;	// 모든 프레임 정보
	int					m_iCurFrm;	// 현재 프레임
	float				m_fAccTime;	// 시간을 누적할 변수

	bool				m_bFinish;	// 재생 끝에 도달여부

public:

	const wstring& GetName() { return this->m_strName; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_fAccTime = 0.f;
		if (m_vecFrm.size() < _iFrameIdx)
		{	
			_iFrameIdx = (int)m_vecFrm.size();
		}
		m_iCurFrm = _iFrameIdx;
	}
	bool IsFinish() { return m_bFinish; }
	tAnimFrm& GetFrame(int _iIdx) {	return m_vecFrm[_iIdx];	}
	UINT GetMaxFrame() { return (UINT)m_vecFrm.size(); }

private:
	void SetName(const wstring& _strName) { this->m_strName = _strName; }	


public:
	void Update();
	void Render(HDC _dc);
	void Create(VTexture* _pTex, Vector2 _vLT, Vector2 _vSliceSize
		, Vector2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	void Save(const wstring& _strRelativePath);
	void Save1ByteVer(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);
	void Load1ByteVer(const wstring& _strRelativePath);


public:
	VAnimation();
	~VAnimation();

	friend class VAnimator;
};

