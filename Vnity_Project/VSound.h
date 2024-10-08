#pragma once
#include "VResource.h"

#include "VSoundManager.h"

class VSound : public VResource
{
private:
	LPDIRECTSOUNDBUFFER		m_pSoundBuffer;	// 소리를 저장하는 공간(메모리)
	DSBUFFERDESC			m_tBuffInfo;
	int						m_iVolume;

public:
	int Load(const wstring& _strPath);

	// 일반 재생
	void Play(bool _bLoop = false);

	// BGM 으로 재생
	void PlayToBGM(bool _bLoop = false);

	void Stop(bool _bReset = false);

	// 볼륨 범위 (0 ~ 100)
	void SetVolume(float _fVolume);

	// 음악파일 위치 조정
	void SetPosition(float _fPosition); // 0 ~ 100 사이

private:
	bool LoadWaveSound(const wstring& _strPath);
	int GetDecibel(float _fVolume);



public:
	VSound();
	virtual ~VSound();


};

