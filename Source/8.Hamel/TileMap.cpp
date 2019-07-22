#include "DXUT.h"
#include "GaBase.h"


TileMap::TileMap()
{
}

TileMap::TileMap(LPDIRECT3DDEVICE9 pd3dDevice)
{
	srand((unsigned int)time(NULL));

	InitTileMap(pd3dDevice);
	m_fTileAngle = 0.5f;
}


TileMap::~TileMap()
{
}

void TileMap::InitTileMap(LPDIRECT3DDEVICE9 pd3dDevice)
{
	for (int i = 0; i < TILE_NUM; i++)
	{
		for (int j = 0; j < TILE_NUM; j++)
		{
			m_pTile[i][j] = new Tile;

			m_pTile[i][j]->CreateTexture(pd3dDevice, L"texture\\tile.png");

			int nRand = rand() % 2;

			switch (nRand)
			{
			case 0:
				m_pTile[i][j]->SetTileID(Tile::TileID::BASIC1);
				break;
			case 1:
				m_pTile[i][j]->SetTileID(Tile::TileID::BASIC2);
				break;
			default:
				break;
			}
			m_pTile[i][j]->SetPosition(336 + (j - i) * TILE_WIDTH / 2, -1680 + (j + i) * TILE_HEIGHT / 2, 0);
			m_pTile[i][j]->m_nTileX = i;
			m_pTile[i][j]->m_nTileY = j;
			m_pTile[i][j]->m_bVisible = true;
		}
	}
	
	SetSoilTile();
	SetWaterTile();
	SetGrassTile();
	SetTree(pd3dDevice);
	SetTengerinTree(pd3dDevice);
	SetStone(pd3dDevice);
	for (int i = 0; i < TILE_NUM; i++)
	{
		for (int j = 0; j < TILE_NUM; j++)
		{
			m_pTile[i][j]->SetTileProperty();
		}
	}
}

void TileMap::Process()
{
	for (int i = 0; i < TILE_NUM; i++)
	{
		for (int j = 0; j < TILE_NUM; j++)
		{
			if (IsPointOnTile(m_pTile[i][j], MOUSE()->m_fCursorPosX - MOUSE()->m_fMouseX, MOUSE()->m_fCursorPosY - MOUSE()->m_fMouseY))
			{
				m_pTile[i][j]->SetColor(1.0f, 0.5f, 0.5f, 1.0f);
				MOUSE()->m_nGameX = i;
				MOUSE()->m_nGameY = j;
			}
			else
			{
				m_pTile[i][j]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	}
}

bool TileMap::IsPointOnTile(Tile* pTile, float x, float y)
{
	D3DXVECTOR2 v1 = D3DXVECTOR2(pTile->m_vPosition.x, pTile->m_vPosition.y + TILE_HEIGHT / 2);
	D3DXVECTOR2 v2 = D3DXVECTOR2(pTile->m_vPosition.x + TILE_WIDTH / 2, pTile->m_vPosition.y);
	D3DXVECTOR2 v3 = D3DXVECTOR2(pTile->m_vPosition.x + TILE_WIDTH, pTile->m_vPosition.y + TILE_HEIGHT / 2);
	D3DXVECTOR2 v4 = D3DXVECTOR2(pTile->m_vPosition.x + TILE_WIDTH / 2, pTile->m_vPosition.y + TILE_HEIGHT);

	float d1 = v1.y - (-m_fTileAngle * v1.x);
	float d2 = v2.y - (m_fTileAngle * v2.x);
	float d3 = v3.y - (-m_fTileAngle * v3.x);
	float d4 = v4.y - (m_fTileAngle * v4.x);

	float result1 = -m_fTileAngle * x - y + d1;
	float result2 = m_fTileAngle * x - y + d2;
	float result3 = -m_fTileAngle * x - y + d3;
	float result4 = m_fTileAngle * x - y + d4;

	if (result1 < 0.0f && result2 < 0.0f && result3 > 0.0f && result4 > 0.0f)
	{
		return true;
	}

	return false;
}

void TileMap::SetSoilTile()
{
	// set soil tile
	for (int i = 1; i < 12; i++)
	{
		for (int j = 1; j < 12; j++)
		{
			m_pTile[i][j]->SetTileID(Tile::TileID::SAND);
		}
	}
}

void TileMap::SetWaterTile()
{
	// set water tile
	for (int i = 22; i < 24; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_pTile[j][i]->SetTileID(Tile::TileID::WATER);
			if (j == 6)
			{
				m_pTile[j][i]->SetTileID(Tile::TileID::BRIDGE);
			}
		}
	}
	for (int i = 18; i < 20; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_pTile[j][i]->SetTileID(Tile::TileID::WATER);
			if (j == 2)
			{
				m_pTile[j][i]->SetTileID(Tile::TileID::BRIDGE);
			}
		}
	}
	for (int i = 18; i < 22; i++)
	{
		for (int j = 8; j < 11; j++)
		{
			m_pTile[j][i]->SetTileID(Tile::TileID::WATER);
		}
	}
	for (int i = 11; i < 14; i++)
	{
		for (int j = 18; j < 32 - i; j++)
		{
			m_pTile[i][j]->SetTileID(Tile::TileID::WATER);
		}
	}
}

void TileMap::SetGrassTile()
{
	for (int i = 2; i < 6; i++)
	{
		for (int j = 25; j < 29; j++)
		{
			m_pTile[i][j]->SetTileID(Tile::TileID::GRASS);
		}
	}

	for (int i = 21; i < 25; i++)
	{
		for (int j = 5; j < 9; j++)
		{
			m_pTile[i][j]->SetTileID(Tile::TileID::GRASS);
		}
	}
}

void TileMap::SetTree(LPDIRECT3DDEVICE9 pd3dDevice)
{
	nTreeCount = 0;

	for (int i = 0; i < TREE_NUM; i++)
	{
		m_pTree[i] = new RenderObject;

		m_pTree[i]->CreateTexture(pd3dDevice, L"texture\\nature.png");

		m_pTree[i]->SetRect(0, 156, 0, 270);
		m_pTree[i]->m_bVisible = true;
	}

	for (int j = 0; j < 18; j++)
	{
		m_pTree[nTreeCount]->SetPosition(m_pTile[j][0]->m_vPosition.x - 14, m_pTile[j][0]->m_vPosition.y + 64 - 270, 0);
		m_pTree[nTreeCount + 1]->SetPosition(m_pTile[0][j]->m_vPosition.x - 14, m_pTile[0][j]->m_vPosition.y + 64 - 270, 0);
		
		m_pTile[j][0]->SetTileID(Tile::TileID::TREE);
		m_pTile[0][j]->SetTileID(Tile::TileID::TREE);
		nTreeCount += 2;
	}
}

void TileMap::SetTengerinTree(LPDIRECT3DDEVICE9 pd3dDevice)
{
	nTangerinTreeCount = 0;

	for (int i = 0; i < TANGERIN_TREE_NUM; i++)
	{
		m_pTangerin_Tree[i] = new RenderObject;

		m_pTangerin_Tree[i]->CreateTexture(pd3dDevice, L"texture\\nature.png");

		m_pTangerin_Tree[i]->SetRect(0, 156, 270, 536);
		m_pTangerin_Tree[i]->m_bVisible = true;
	}

	m_pTangerin_Tree[nTangerinTreeCount]->SetPosition(m_pTile[19][10]->m_vPosition.x - 14, m_pTile[19][10]->m_vPosition.y + 64 - 266, 0);
	m_pTile[19][10]->SetTileID(Tile::TileID::TANGERIN_TREE);
	nTangerinTreeCount++;
	for (int i = 9; i < 11; i++)
	{
		m_pTangerin_Tree[nTangerinTreeCount]->SetPosition(m_pTile[20][i]->m_vPosition.x - 14, m_pTile[20][i]->m_vPosition.y + 64 - 266, 0);
		m_pTile[20][i]->SetTileID(Tile::TileID::TANGERIN_TREE);
		nTangerinTreeCount++;
	}

	for (int i = 25; i < 27; i++)
	{
		m_pTangerin_Tree[nTangerinTreeCount]->SetPosition(m_pTile[27][i]->m_vPosition.x - 14, m_pTile[27][i]->m_vPosition.y + 64 - 266, 0);
		m_pTile[27][i]->SetTileID(Tile::TileID::TANGERIN_TREE);
		nTangerinTreeCount++;
	}
	m_pTangerin_Tree[nTangerinTreeCount]->SetPosition(m_pTile[28][25]->m_vPosition.x - 14, m_pTile[28][25]->m_vPosition.y + 64 - 266, 0);
	m_pTile[28][25]->SetTileID(Tile::TileID::TANGERIN_TREE);
	nTangerinTreeCount++;

	for (int i = 10; i < 14; i++)
	{
		m_pTangerin_Tree[nTangerinTreeCount]->SetPosition(m_pTile[30][i]->m_vPosition.x - 14, m_pTile[30][i]->m_vPosition.y + 64 - 266, 0);
		m_pTile[30][i]->SetTileID(Tile::TileID::TANGERIN_TREE);
		nTangerinTreeCount++;
	}

	for (int i = 14; i < 16; i++)
	{
		m_pTangerin_Tree[nTangerinTreeCount]->SetPosition(m_pTile[i][27]->m_vPosition.x - 14, m_pTile[i][27]->m_vPosition.y + 64 - 266, 0);
		m_pTile[i][27]->SetTileID(Tile::TileID::TANGERIN_TREE);
		nTangerinTreeCount++;
	}
	m_pTangerin_Tree[nTangerinTreeCount]->SetPosition(m_pTile[12][28]->m_vPosition.x - 14, m_pTile[12][28]->m_vPosition.y + 64 - 266, 0);
	m_pTile[12][28]->SetTileID(Tile::TileID::TANGERIN_TREE);
	nTangerinTreeCount++;
	for (int i = 13; i < 15; i++)
	{
		m_pTangerin_Tree[nTangerinTreeCount]->SetPosition(m_pTile[i][28]->m_vPosition.x - 14, m_pTile[i][28]->m_vPosition.y + 64 - 266, 0);
		m_pTile[i][28]->SetTileID(Tile::TileID::TANGERIN_TREE);
		nTangerinTreeCount++;
	}
}

void TileMap::SetStone(LPDIRECT3DDEVICE9 pd3dDevice)
{
	for (int i = 0; i < STONE_NUM; i++)
	{
		m_pStone[i] = new RenderObject;

		m_pStone[i]->CreateTexture(pd3dDevice, L"texture\\nature.png");

		m_pStone[i]->SetRect(0, 128, 536, 624);
		m_pStone[i]->m_bVisible = true;
	}

	m_pStone[0]->SetPosition(m_pTile[17][5]->m_vPosition.x, m_pTile[17][5]->m_vPosition.y + 64 - 88, 0);
	m_pTile[17][5]->SetTileID(Tile::TileID::STONE);

	m_pStone[1]->SetPosition(m_pTile[23][18]->m_vPosition.x, m_pTile[23][18]->m_vPosition.y + 64 - 88, 0);
	m_pTile[23][18]->SetTileID(Tile::TileID::STONE);

	m_pStone[2]->SetPosition(m_pTile[8][15]->m_vPosition.x, m_pTile[8][15]->m_vPosition.y + 64 - 88, 0);
	m_pTile[8][15]->SetTileID(Tile::TileID::STONE);

	m_pStone[3]->SetPosition(m_pTile[7][29]->m_vPosition.x, m_pTile[7][29]->m_vPosition.y + 64 - 88, 0);
	m_pTile[7][29]->SetTileID(Tile::TileID::STONE);

	m_pStone[4]->SetPosition(m_pTile[1][21]->m_vPosition.x, m_pTile[1][21]->m_vPosition.y + 64 - 88, 0);
	m_pTile[1][21]->SetTileID(Tile::TileID::STONE);

	m_pStone[5]->SetPosition(m_pTile[28][31]->m_vPosition.x, m_pTile[28][31]->m_vPosition.y + 64 - 88, 0);
	m_pTile[28][31]->SetTileID(Tile::TileID::STONE);

	m_pStone[6]->SetPosition(m_pTile[25][2]->m_vPosition.x, m_pTile[25][2]->m_vPosition.y + 64 - 88, 0);
	m_pTile[25][2]->SetTileID(Tile::TileID::STONE);

	m_pStone[7]->SetPosition(m_pTile[14][8]->m_vPosition.x, m_pTile[14][8]->m_vPosition.y + 64 - 88, 0);
	m_pTile[14][8]->SetTileID(Tile::TileID::STONE);

	m_pStone[8]->SetPosition(m_pTile[16][16]->m_vPosition.x, m_pTile[16][16]->m_vPosition.y + 64 - 88, 0);
	m_pTile[16][16]->SetTileID(Tile::TileID::STONE);

	m_pStone[9]->SetPosition(m_pTile[31][8]->m_vPosition.x, m_pTile[31][8]->m_vPosition.y + 64 - 88, 0);
	m_pTile[31][8]->SetTileID(Tile::TileID::STONE);
}