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
	// 템플릿내부에서 Iterator를 사용하려면 typename을 적어주어야한다. (문법)
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
/// 파일의 특정한 문자(EndKeyword)를 만날때까지 버퍼에 담아주는 함수('\n'문자 포함해서 담아줄거임)
/// </summary>
/// <param name="_pOutBuff">문자를 담아둘 버퍼</param>
/// <param name="_pFile">어떤 파일에서 읽어올지</param>
/// <param name="_cEndKeyword">마지막이될 문자</param>
void FScanf(char* _pOutBuff, FILE* _pFile, char _cEndKeyword);


void SaveWString(const wstring& _str, FILE* _pFile);
void LoadWString(wstring& _str, FILE* pFile);
