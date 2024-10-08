#include "VTile.h"
#include "VTexture.h"

VTile::VTile()
	:m_pTileTex(nullptr)
	, m_iImgIdx(48)
{
	SetScale(Vector2(TILE_SIZE, TILE_SIZE));
}

VTile::~VTile()
{
}



void VTile::Awake()
{
}

void VTile::Start()
{
}

void VTile::Render(HDC _dc)
{
	if (this->m_pTileTex == nullptr || m_iImgIdx < 0)
	{	// if : ���� �������� Ÿ���� ���ų�, ���� �ε����� ������ ��� ����
		return;
	}

	UINT iWidth = m_pTileTex->GetWidth();
	UINT iHeight = m_pTileTex->GetHeight();

	UINT iMaxCol = iWidth / TILE_SIZE;		// �̹����� �ִ� ����
	UINT iMaxRow = iHeight / TILE_SIZE;		// �̹����� �ִ� ����

	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;	// ���� ������ ������ġ
	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;	// ���� ������ ������ġ

	if (iMaxRow <= iCurRow)
	{	// if : ������ ���� ���� ��ġ�� �ִ� ��ġ�� ���ų� ���簡 �� Ŭ��� (�̹��� ������ ��� �ε�����)
		assert(nullptr);	// Assert�� �Ǹ� ���� �ִ°���
		return;
	}




	Vector2 vRenderPos = VCamera::GetInst()->GetWorldToRenderPos(GetPos());
	Vector2 vScale = GetScale();

	BitBlt(_dc
		, (int)vRenderPos.x
		, (int)vRenderPos.y
		, (int)vScale.x
		, (int)vScale.y
		, m_pTileTex->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);

}

void VTile::Update()
{

}

void VTile::Save(FILE* _pFile)
{
	// TODO : ������, �����ϵ� �߰� ����
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void VTile::Load(FILE* _pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}
