#pragma once

class VObject;
class VTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,

};

struct tCamEffect
{
	CAM_EFFECT	eEffect;		// 카메라 효과
	float		fDuration;	// 효과 진행 얼마나 걸릴지 시간
	float		fCurTime;		// 카메라 효과 현재 진행된 시간

};


class VCamera
{
	SINGLETON(VCamera);

private:
	Vector2				m_vLookAt;			// 현재 카메라가 보고있는 위치 (현재 타겟 위치)
	Vector2				m_vCurLookAt;		// 이전위치와 현재위치의 보정위치
	Vector2				m_vPrevLookAt;		// 카메라가 이전프레임에 보고있던 위치

	VObject*			m_pTargetObj;		// 카메라가 보고있는 타겟

	Vector2				m_vDiff;			// 화면 중앙좌표와 카메라 LookAt 좌표간의 차이값

	float				m_fTime;			// 타겟을 따라가는데 걸리는 시간
	float				m_fSpeed;			// 타겟을 따라가는 속도
	float				m_fAccTime;			// 누적시간

	list<tCamEffect>	m_listCamEffect;
	VTexture*			m_pVeilTex;			// 카메라 가림막 텍스쳐(페이드 인, 아웃에서 사용될 예정)	


public:
	void SetLookAt(Vector2 _vLook)
	{
		this->m_vLookAt = _vLook;
		double fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = (float)fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}
	void SetTarget(VObject* _pTarget) { this->m_pTargetObj = _pTarget; }
	Vector2 GetLookAt() { return m_vCurLookAt; }
	Vector2 GetWorldToRenderPos(Vector2 _vWorldPos) { return _vWorldPos - m_vDiff; }
	Vector2 GetRenderToWorldPos(Vector2 _vRenderPos) { return _vRenderPos + m_vDiff; }

	void FadeIn(float _fDuration)
	{
		if (_fDuration <= 0.f)
		{
			assert(nullptr);
			return;
		}

		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;
		
		m_listCamEffect.push_back(ef);
	}
	void FadeOut(float _fDuration)
	{
		if (_fDuration <= 0.f)
		{
			assert(nullptr);
			return;
		}
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);
	}

public:
	void Init();
	void Update();
	void Render(HDC _dc);


private:
	void CalDiff();
};

