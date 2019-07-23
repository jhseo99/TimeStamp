#pragma once

class Stage
{
public:
	Stage();
	~Stage();

public:
	TileMap* m_pTileMap;
	RenderObject* m_pWater;
	Player* m_pPlayer;

	RenderObject* m_pUI;

	AStar* m_pAStar;

	std::vector<RenderObject*> m_vecRenderObject;

public:
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	void Update();
	void Render();

public:
	void MoveWorld();
	void UpdatePath();
};

