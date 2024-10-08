#pragma once
// sound 용도 - 헤더 순서 중요
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

// 코드
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

class VSound;

class VSoundManager
{
	SINGLETON(VSoundManager);

private:
	LPDIRECTSOUND8	m_pSound;	// 사운드카드 대표 객체
	VSound*			m_pBGM;		// 현재 지정된 BGM Sound

public:
	int Init(void);
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
	void RegisterToBGM(VSound* _pSound);

};

