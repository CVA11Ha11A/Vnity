#pragma once

class VObject;
class VAI;

void CreateObject(const VObject* _pObj, GROUP_TYPE _eGroup);
void Destroy(VObject* _pObj);
void ChangeScene(E_SCENE_TYPE _eNext);
void ChangeAIState(VAI* _pAI, MON_STATE _eNextState);


template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
  {	
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (_vec[i] != nullptr)
		{			
			delete _vec[i];
			_vec[i] = nullptr;
		}
	}
	_vec.clear();
}		// Safe_Delete_Vec()

template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	// ���ø����ο��� Iterator�� ����Ϸ��� typename�� �����־���Ѵ�. (����)
	typename map<T1, T2>::iterator iter = _map.begin();
	
	for (; iter != _map.end(); ++iter)
	{
		if (iter->second != nullptr)
		{
			delete iter->second;
		}
	}
	_map.clear();
}		// Safe_Delete_Map()

void FScanf(char* _pOutBuff, FILE* _pFile);
/// <summary>
/// ������ Ư���� ����(EndKeyword)�� ���������� ���ۿ� ����ִ� �Լ�('\n'���� �����ؼ� ����ٰ���)
/// </summary>
/// <param name="_pOutBuff">���ڸ� ��Ƶ� ����</param>
/// <param name="_pFile">� ���Ͽ��� �о����</param>
/// <param name="_cEndKeyword">�������̵� ����</param>
void FScanf(char* _pOutBuff, FILE* _pFile, char _cEndKeyword);


void SaveWString(const wstring& _str, FILE* _pFile);
void LoadWString(wstring& _str, FILE* pFile);
