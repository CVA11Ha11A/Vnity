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
	{	// if : �� �������� ���ӽð��� �ʰ��Ѵٸ� ����

		++m_iCurFrm;

		if (m_vecFrm.size() <= m_iCurFrm)
		{	// if : �ִϸ��̼��� ��� �������� ������ٸ� ����
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

	vPos += m_vecFrm[m_iCurFrm].vOffset;	// Obejct Position�� Offset ��ŭ �̵��ϱ�

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

	// Animation�� �̸��� ���� (������ ����ȭ)	
	SaveWString(m_strName, pFile);

	// Animation�� ����ϴ� TexturePointer(Texture)
	SaveWString(m_pTex->GetKey(), pFile);
	SaveWString(m_pTex->GetRelativePath(), pFile);

	// ������ ����
	size_t iFrameCount = m_vecFrm.size();
	fwrite(&iFrameCount, sizeof(size_t), 1, pFile);

	// ��� ������ ����
	// vector.data() : vector���ο� �����͸� �����ϴ� �迭�� �����͸� ��ȯ����
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

	// Animation �̸� �б�
	LoadWString(m_strName, pFile);

	// { �ؽ���
	wstring strTexKey;
	wstring strTexPath;	// �����
	LoadWString(strTexKey, pFile);
	LoadWString(strTexPath, pFile);
	m_pTex = VResourceManager::GetInst()->LoadTexture(strTexKey, strTexPath);
	// } �ؽ��� 

	// ������ ����
	size_t iFrameCount = 0;
	fread(&iFrameCount, sizeof(size_t), 1, pFile);

	// ��� ������ ����
	m_vecFrm.resize(iFrameCount);		// �޸� ����ȭ ������ �Ǿ �ݺ������� ���ƺ���
	fread(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);



	fclose(pFile);

}		// Load()

// �޸������� ����������� ����� �б� ���� ������ save
void VAnimation::Save1ByteVer(const wstring& _strRelativePath)
{
	wstring strFilePath = VPathManager::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	assert(pFile);

	// Animation�� �̸��� ���� (������ ����ȭ)
	fprintf(pFile, "[Animation Name]\n");
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// Animation�� ����ϴ� TexturePointer(Texture)
	fprintf(pFile, "[Texture Name]\n");
	strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture Path]\n");
	strName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");


	// ������ ����
	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d\n", (int)m_vecFrm.size());


	// ��� ������ ����	
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

	// Animation�� �̸��� �о�´�.
	string str;		// wstring���� ��ȯ�� ���� string��ü
	char szBuff[256] = {};		// �о�ð��� ��Ƶ� buffer

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);		
	str = szBuff;
	m_strName = wstring(str.begin(), str.end());

	// Texture : Animation�� ����ϴ� TexturePointer(Texture)
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;
	wstring strTexKey = wstring(str.begin(), str.end());

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);

	str = szBuff;
	wstring strTexPath = wstring(str.begin(), str.end());

	m_pTex = VResourceManager::GetInst()->LoadTexture(strTexKey, strTexPath);	


	// ������ ����
	FScanf(szBuff, pFile);
	int iFrameCount = 0;
	//fscanf_s(pFile, "%d", &iFrameCount);	TODO : �ش� �Լ� �׽�Ʈ �ʿ� (�ؽ��Ŀ��� ��������)

	tAnimFrm frm = {};

	// ��� ������ ����	
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
				fscanf_s(pFile, "%d", &pt.x);	// ���ٷ� ��� ���� fscanf_s(pFile, "%d, %d", &pt.x, &pt.y);
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
