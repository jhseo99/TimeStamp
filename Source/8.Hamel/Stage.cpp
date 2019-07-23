#include "DXUT.h"
#include "GaBase.h"


Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	m_pTileMap = new TileMap(pd3dDevice);

	m_vecRenderObject.clear();

	for (int i = 0; i < TILE_NUM; i++)
	{
		for (int j = 0; j < TILE_NUM; j++)
		{
			m_vecRenderObject.push_back(m_pTileMap->m_pTile[i][j]);
		}
	}
	for (int i = 0; i < TREE_NUM; i++)
	{
		m_vecRenderObject.push_back(m_pTileMap->m_pTree[i]);
	}
	for (int i = 0; i < TANGERIN_TREE_NUM; i++)
	{
		m_vecRenderObject.push_back(m_pTileMap->m_pTangerin_Tree[i]);
	}
	for (int i = 0; i < STONE_NUM; i++)
	{
		m_vecRenderObject.push_back(m_pTileMap->m_pStone[i]);
	}

	m_pWater = new RenderObject;
	m_pWater->CreateTexture(pd3dDevice, L"texture\\water.png");
	m_pWater->SetRect(0, 800, 0, 600);
	m_pWater->SetPosition(0, 0, 0);
	m_pWater->m_bVisible = true;

	m_pPlayer = new Player;
	m_pPlayer->CreateTexture(pd3dDevice, L"texture\\Player.png");
	m_pPlayer->SetRect(0, 128, 0, 130);
	m_pPlayer->SetPosition(m_pTileMap->m_pTile[31][31]->m_vPosition.x, m_pTileMap->m_pTile[31][31]->m_vPosition.y - 64, 0);
	m_pPlayer->m_bVisible = true;
	m_vecRenderObject.push_back(m_pPlayer);

	m_pUI = new RenderObject;
	m_pUI->CreateTexture(pd3dDevice, L"texture\\ui.png");
	m_pUI->SetRect(0, 800, 0, 600);
	m_pUI->SetPosition(0, 0, 0);
	m_pUI->m_bVisible = true;

	m_pAStar = new AStar;
	for (int i = 0; i < TILE_NUM; i++)
	{
		for (int j = 0; j < TILE_NUM; j++)
		{
			m_pAStar->m_pTileSet[i][j] = m_pTileMap->m_pTile[i][j];
		}
	}
}

void Stage::Update()
{
	m_pTileMap->Process();
	m_pPlayer->Process(m_pTileMap);

	MoveWorld();
	UpdatePath();
}

void Stage::Render()
{
	m_pWater->Render();

	for (int i = 0; i < TILE_NUM; i++)
	{
		for (int j = 0; j < TILE_NUM; j++)
		{
			m_pTileMap->m_pTile[i][j]->Render();
		}
	}
	for (int i = 0; i < TREE_NUM; i++)
	{
		m_pTileMap->m_pTree[i]->Render();
	}
	for (int i = 0; i < TANGERIN_TREE_NUM; i++)
	{
		m_pTileMap->m_pTangerin_Tree[i]->Render();
	}
	for (int i = 0; i < STONE_NUM; i++)
	{
		m_pTileMap->m_pStone[i]->Render();
	}

	m_pPlayer->Render();
	m_pUI->Render();
}

void Stage::MoveWorld()
{
	if (MOUSE()->m_bCameraeMove)
	{
		for (int i = 0; i < m_vecRenderObject.size(); i++)
		{
			D3DXMatrixTranslation(&m_vecRenderObject[i]->m_matWorld, MOUSE()->m_fMouseX, MOUSE()->m_fMouseY, 0);
		}
	}

	MOUSE()->m_bCameraeMove = false;
	if (MOUSE()->m_fCursorPosX <= 0.0f)
	{
		MOUSE()->m_fMouseX += MOUSE()->m_fSensitivity;
		MOUSE()->m_bCameraeMove = true;
	}
	if (MOUSE()->m_fCursorPosX >= 799.0f)
	{
		MOUSE()->m_fMouseX -= MOUSE()->m_fSensitivity;
		MOUSE()->m_bCameraeMove = true;
	}
	if (MOUSE()->m_fCursorPosY <= 0.0f)
	{
		MOUSE()->m_fMouseY += MOUSE()->m_fSensitivity;
		MOUSE()->m_bCameraeMove = true;
	}
	if (MOUSE()->m_fCursorPosY >= 599.0f)
	{
		MOUSE()->m_fMouseY -= MOUSE()->m_fSensitivity;
		MOUSE()->m_bCameraeMove = true;
	}
}

void Stage::UpdatePath()
{
	if (MOUSE()->m_bCurrentClickRight)
	{
		if (m_pTileMap->m_pTile[MOUSE()->m_nGameX][MOUSE()->m_nGameY]->m_bMovable && 
			m_pTileMap->m_pTile[m_pPlayer->m_nPlayerX][m_pPlayer->m_nPlayerY] != m_pTileMap->m_pTile[MOUSE()->m_nGameX][MOUSE()->m_nGameY])
		{
			m_pAStar->PathFind(m_pTileMap->m_pTile[m_pPlayer->m_nPlayerX][m_pPlayer->m_nPlayerY], m_pTileMap->m_pTile[MOUSE()->m_nGameX][MOUSE()->m_nGameY]);
			m_pPlayer->SetMovePath(m_pAStar->m_deqBestPath);
		}
	}

	for (int i = 0; i < m_pAStar->m_deqBestPath.size(); i++)
	{
		m_pAStar->m_deqBestPath[i]->SetColor(0.0f, 0.0f, 1.0f, 1.0f);
	}

	//for (int i = 0; i < m_pAStar->m_vecOpenNode.size(); i++)
	//{
	//	m_pAStar->m_vecOpenNode[i]->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	//}
	//for (int i = 0; i < m_pAStar->m_vecCloseNode.size(); i++)
	//{
	//	m_pAStar->m_vecCloseNode[i]->SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	//}
	
	
}