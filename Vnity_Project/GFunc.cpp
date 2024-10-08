#include "pch.h"
#include "GFunc.h"

#include "VScene.h"
#include "VEventManager.h"
#include "VSceneManager.h"
#include "VAI.h"

/// <summary>
/// Event메니저에게 Object 생성이벤트 추가하는 함수
/// </summary>
/// <param name="_pObj">추가할 오브젝트의 포인터</param>
/// <param name="_eGroup">어떤 오브젝트의 종류인지</param>
void CreateObject(const VObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = E_EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	VEventManager::GetInst()->AddEvent(evn);
}

void Destroy(VObject* _pObj)
{
	tEvent evn = {};
	evn.eEven = E_EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;	

	VEventManager::GetInst()->AddEvent(evn);
}

void ChangeScene(E_SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEven = E_EVENT_TYPE::SCENE_CHANGE;	
	evn.lParam = (DWORD_PTR)_eNext;

	VEventManager::GetInst()->AddEvent(evn);
}		// ChangeScene()

void ChangeAIState(VAI* _pAI, MON_STATE _eNextState)
{
	tEvent evn = {};
	evn.eEven = E_EVENT_TYPE::CHANGE_AI_STATE;
	evn.lParam = (DWORD_PTR)_pAI;
	evn.wParam = (DWORD_PTR)_eNextState;

	VEventManager::GetInst()->AddEvent(evn);
}		// ChangeAIState()




void FScanf(char* _pOutBuff, FILE* _pFile)
{
	int i = 0;
	while (true)
	{
		char c = (char)getc(_pFile);
		if (c == '\n')
		{
			_pOutBuff[i++] = '\0';
			break;
		}
		else
		{
			_pOutBuff[i++] += c;
		}
	}
}		// FScanf()

void FScanf(char* _pOutBuff, FILE* _pFile, char _cEndKeyword)
{
	int i = 0;
	while (true)
	{
		char c = (char)getc(_pFile);
		if (c == '\n')
		{			
			_pOutBuff[i++] = '\0';
			break;
		}
		else if (c == _cEndKeyword)
		{
			long pos = ftell(_pFile); // 현재 위치 저장
			char cTemp = (char)getc(_pFile); // 문자 읽기
			if (cTemp == '\n')
			{	// 다음에 파일을 읽을경우 \n문자가 나온다면 어차피 한번 건너뛰어지기때문에 
				// 현재 버퍼에 넣어주고 파일의 현재 위치를 한단계넘겨줌
				_pOutBuff[i++] = '\0';
			}
			else
			{	// 원하는 위치 다음에 \0문자가 아닌 진짜 문자가 존재한다면 읽은 위치를 다시 되돌려줌
				fseek(_pFile, pos, SEEK_SET); // 위치 되돌리기				
			}
			break;
		}
		else
		{
			_pOutBuff[i++] += c;
		}
	}	// while

}		// FScanf()

void SaveWString(const wstring& _str, FILE* _pFile)
{
	assert(_pFile);

	const wchar_t* pStrName = _str.c_str();
	size_t iLen = _str.length();

	// 문자 길이 저장
	fwrite(&iLen, sizeof(size_t), 1, _pFile);

	// 문자열 저장
	fwrite(pStrName, sizeof(wchar_t), iLen, _pFile);

}		// SaveWString()

void LoadWString(wstring& _str, FILE* pFile)
{
	// 문자열의 길이를 가져오기 (처음에 저장한 size_t타입의 변수)
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, pFile);
	wchar_t szBuff[256] = {};
	// fread는 파일의 Cur포인터가 읽을때마다 읽은 만큼 움직이기 떄문에 그대로 읽는것임
	fread(szBuff, sizeof(wchar_t), iLen, pFile);

	_str = szBuff;

}		// LoadWString()

