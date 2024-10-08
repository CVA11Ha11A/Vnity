#include "pch.h"
#include "GFunc.h"

#include "VScene.h"
#include "VEventManager.h"
#include "VSceneManager.h"
#include "VAI.h"

/// <summary>
/// Event�޴������� Object �����̺�Ʈ �߰��ϴ� �Լ�
/// </summary>
/// <param name="_pObj">�߰��� ������Ʈ�� ������</param>
/// <param name="_eGroup">� ������Ʈ�� ��������</param>
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
			long pos = ftell(_pFile); // ���� ��ġ ����
			char cTemp = (char)getc(_pFile); // ���� �б�
			if (cTemp == '\n')
			{	// ������ ������ ������� \n���ڰ� ���´ٸ� ������ �ѹ� �ǳʶپ����⶧���� 
				// ���� ���ۿ� �־��ְ� ������ ���� ��ġ�� �Ѵܰ�Ѱ���
				_pOutBuff[i++] = '\0';
			}
			else
			{	// ���ϴ� ��ġ ������ \0���ڰ� �ƴ� ��¥ ���ڰ� �����Ѵٸ� ���� ��ġ�� �ٽ� �ǵ�����
				fseek(_pFile, pos, SEEK_SET); // ��ġ �ǵ�����				
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

	// ���� ���� ����
	fwrite(&iLen, sizeof(size_t), 1, _pFile);

	// ���ڿ� ����
	fwrite(pStrName, sizeof(wchar_t), iLen, _pFile);

}		// SaveWString()

void LoadWString(wstring& _str, FILE* pFile)
{
	// ���ڿ��� ���̸� �������� (ó���� ������ size_tŸ���� ����)
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, pFile);
	wchar_t szBuff[256] = {};
	// fread�� ������ Cur�����Ͱ� ���������� ���� ��ŭ �����̱� ������ �״�� �д°���
	fread(szBuff, sizeof(wchar_t), iLen, pFile);

	_str = szBuff;

}		// LoadWString()

