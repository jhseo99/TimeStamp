#include "DXUT.h"
#include "GaBase.h"


Tile::Tile()
{
	Init();
}


Tile::~Tile()
{
}

void Tile::Init()
{
	m_nTileX = 0;
	m_nTileY = 0;
	m_bHit = false;
	m_bMovable = false;
	m_enId = TileID::BASIC1;
	m_pParentNode = NULL;
	m_nGValue = 0;
	m_nFValue = 0;
	m_nFValue = 0;
}

void Tile::SetTileProperty()
{
	switch (m_enId)
	{
	case TileID::BASIC1:
		SetRect(0, 128, 0, 128);
		m_bMovable = true;
		break;
	case TileID::BASIC2:
		SetRect(128, 256, 0, 128);
		m_bMovable = true;
		break;
	case TileID::WATER:
		SetRect(256, 384, 0, 128);
		m_bMovable = false;
		break;
	case TileID::SAND:
		SetRect(384, 512, 0, 128);
		m_bMovable = true;
		break;
	case TileID::GRASS:
		SetRect(512, 640, 0, 128);
		m_bMovable = true;
		break;
	case TileID::BRIDGE:
		SetRect(640, 768, 0, 128);
		m_bMovable = true;
		break;
	case TileID::TREE:
		SetRect(128, 256, 0, 128);
		m_bMovable = false;
		break;
	case TileID::TANGERIN_TREE:
		SetRect(0, 128, 0, 128);
		m_bMovable = false;
		break;
	case TileID::STONE:
		SetRect(128, 256, 0, 128);
		m_bMovable = false;
		break;
	default:
		break;
	}
}