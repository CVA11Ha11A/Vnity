#include "pch.h"
#include "VAnimation.h"

#include "VTimeManager.h"
#include "VPathManager.h"
#include "VResourceManager.h"

#include "VAnimator.h"
#include "VTexture.h"
#include "VObject.h"
#include "VCamera.h"

VAnimation::VAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0)
	, m_bFinish(false)
{
}

VAnimation::~VAnimation()
{
}



void VAnimation::Update()
{
	if (m_bFinish == true)
	{
		return;
	}


	m_fAccTime += DeltaTime;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{	// if : 한 프레임의 지속시간을 초과한다면 진입

		++m_iCurFrm;

		if (m_vecFrm.size() <= m_iCurFrm)
		{	// if : 애니메이션의 모든 프레임을 재생헀다면 진입
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;

	}
}

void VAnimation::Render(HDC _dc)
{
	if (m_bFinish == true)
	{
		return;
	}

	VObject* pObj = m_pAnimator->GetObj();
	Vector2 vPos = pObj->GetPos();

	vPos += m_vecFrm[m_iCurFrm].vOffset;	// Obejct Position에 Offset 만큼 이동하기

	vPos = VCamera::GetInst()->GetWorldToRenderPos(vPos);

	TransparentBlt(_dc
		, (int)vPos.x - (int)m_vecFrm[m_iCurFrm].vSlice.x / (int)2.f
		, (int)vPos.y - (int)m_vecFrm[m_iCurFrm].vSlice.y / (int)2.f
		, (int)m_vecFrm[m_iCurFrm].vSlice.x
		, (int)m_vecFrm[m_iCurFrm].vSlice.y
		, m_pTex->GetDC()
		, (int)m_vecFrm[m_iCurFrm].vLT.x
		, (int)m_vecFrm[m_iCurFrm].vLT.y
		, (int)m_vecFrm[m_iCurFrm].vSlice.x
		, (int)m_vecFrm[m_iCurFrm].vSlice.y
		, RGB(255, 0, 255));

}

void VAnimation::Create(VTexture* _pTex, Vector2 _vLT,
	Vector2 _vSliceSize, Vector2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;
	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * (float)i;

		m_vecFrm.push_back(frm);
	}

}

void VAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = VPathManager::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	assert(pFile);

	// Animation의 이름을 저장 (데이터 직렬화)	
	SaveWString(m_strName, pFile);

	// Animation이 사용하는 TexturePointer(Texture)
	SaveWString(m_pTex->GetKey(), pFile);
	SaveWString(m_pTex->GetRelativePath(), pFile);

	// 프레임 개수
	size_t iFrameCount = m_vecFrm.size();
	fwrite(&iFrameCount, sizeof(size_t), 1, pFile);

	// 모든 프레임 정보
	// vector.data() : vector내부에 데이터를 관리하는 배열의 포인터를 반환해줌
	// https://cplusplus.com/reference/vector/vector/data/
	fwrite(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);

	fclose(pFile);

}		// Save()

void VAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = VPathManager::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	// Animation 이름 읽기
	LoadWString(m_strName, pFile);

	// { 텍스쳐
	wstring strTexKey;
	wstring strTexPath;	// 상대경로
	LoadWString(strTexKey, pFile);
	LoadWString(strTexPath, pFile);
	m_pTex = VResourceManager::GetInst()->LoadTexture(strTexKey, strTexPath);
	// } 텍스쳐 

	// 프레임 개수
	size_t iFrameCount = 0;
	fread(&iFrameCount, sizeof(size_t), 1, pFile);

	// 모든 프레임 정보
	m_vecFrm.resize(iFrameCount);		// 메모리 단편화 방지가 되어서 반복문보다 좋아보임
	fread(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);



	fclose(pFile);

}		// Load()

// 메모장으로 오픈했을경우 사람이 읽기 쉬운 버전의 save
void VAnimation::Save1ByteVer(const wstring& _strRelativePath)
{
	wstring strFilePath = VPathManager::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	assert(pFile);

	// Animation의 이름을 저장 (데이터 직렬화)
	fprintf(pFile, "[Animation Name]\n");
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// Animation이 사용하는 TexturePointer(Texture)
	fprintf(pFile, "[Texture Name]\n");
	strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture Path]\n");
	strName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");


	// 프레임 개수
	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d\n", (int)m_vecFrm.size());


	// 모든 프레임 정보	
	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fprintf(pFile, "[Frame Index]\n");
		fprintf(pFile, "%d\n", (int)i);

		fprintf(pFile, "[Left Top]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vLT.x, (int)m_vecFrm[i].vLT.y);

		fprintf(pFile, "[Slice Size]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vSlice.x, (int)m_vecFrm[i].vSlice.y);

		fprintf(pFile, "[Offset]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vOffset.x, (int)m_vecFrm[i].vOffset.y);

		fprintf(pFile, "[Duration]\n");
		fprintf(pFile, "%f\n", m_vecFrm[i].fDuration);

		fprintf(pFile, "\n\n");
	}

	fclose(pFile);

}		// Save1ByteVer()

void VAnimation::Load1ByteVer(const wstring& _strRelativePath)
{
	wstring strFilePath = VPathManager::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	// Animation의 이름을 읽어온다.
	string str;		// wstring으로 변환을 위한 string개체
	char szBuff[256] = {};		// 읽어올것을 담아둘 buffer

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);		
	str = szBuff;
	m_strName = wstring(str.begin(), str.end());

	// Texture : Animation이 사용하는 TexturePointer(Texture)
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;
	wstring strTexKey = wstring(str.begin(), str.end());

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);

	str = szBuff;
	wstring strTexPath = wstring(str.begin(), str.end());

	m_pTex = VResourceManager::GetInst()->LoadTexture(strTexKey, strTexPath);	


	// 프레임 개수
	FScanf(szBuff, pFile);
	int iFrameCount = 0;
	//fscanf_s(pFile, "%d", &iFrameCount);	TODO : 해당 함수 테스트 필요 (텍스쳐에서 막혔었음)

	tAnimFrm frm = {};

	// 모든 프레임 정보	
	for (int i = 0; i < iFrameCount; ++i)
	{
		POINT pt = {};

		while (true)
		{
			FScanf(szBuff, pFile);

			if (!strcmp("[Frame Index]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
			}
			else if (!strcmp("[Left Top]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);	// 한줄로 요약 가능 fscanf_s(pFile, "%d, %d", &pt.x, &pt.y);
				fscanf_s(pFile, "%d", &pt.y);

				frm.vLT = pt;
			}
			else if (!strcmp("[Slice Size]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);

				frm.vSlice = pt;

			}
			else if (!strcmp("[Offset]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);

				frm.vOffset = pt;
			}
			else if (!strcmp("[Duration]", szBuff))
			{
				fscanf_s(pFile, "%f", &frm.fDuration);				
			}

		}	// while()
	}	// for()

	fclose(pFile);

}		// Load()
