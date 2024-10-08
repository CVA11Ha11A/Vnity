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
	{	// if : 현재 참조중인 타일이 없거나, 참조 인덱스가 음수일 경우 리턴
		return;
	}

	UINT iWidth = m_pTileTex->GetWidth();
	UINT iHeight = m_pTileTex->GetHeight();

	UINT iMaxCol = iWidth / TILE_SIZE;		// 이미지의 최대 세로
	UINT iMaxRow = iHeight / TILE_SIZE;		// 이미지의 최대 가로

	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;	// 내가 참조할 가로위치
	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;	// 내가 참조할 세로위치

	if (iMaxRow <= iCurRow)
	{	// if : 참조할 현재 새로 위치가 최대 위치와 같거나 현재가 더 클경우 (이미지 범위를 벗어난 인덱스임)
		assert(nullptr);	// Assert가 되면 문제 있는거임
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
	// TODO : 포지션, 스케일등 추가 저장
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void VTile::Load(FILE* _pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}
