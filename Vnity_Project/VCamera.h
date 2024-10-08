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
	CAM_EFFECT	eEffect;		// ī�޶� ȿ��
	float		fDuration;	// ȿ�� ���� �󸶳� �ɸ��� �ð�
	float		fCurTime;		// ī�޶� ȿ�� ���� ����� �ð�

};


class VCamera
{
	SINGLETON(VCamera);

private:
	Vector2				m_vLookAt;			// ���� ī�޶� �����ִ� ��ġ (���� Ÿ�� ��ġ)
	Vector2				m_vCurLookAt;		// ������ġ�� ������ġ�� ������ġ
	Vector2				m_vPrevLookAt;		// ī�޶� ���������ӿ� �����ִ� ��ġ

	VObject*			m_pTargetObj;		// ī�޶� �����ִ� Ÿ��

	Vector2				m_vDiff;			// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���̰�

	float				m_fTime;			// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float				m_fSpeed;			// Ÿ���� ���󰡴� �ӵ�
	float				m_fAccTime;			// �����ð�

	list<tCamEffect>	m_listCamEffect;
	VTexture*			m_pVeilTex;			// ī�޶� ������ �ؽ���(���̵� ��, �ƿ����� ���� ����)	


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

