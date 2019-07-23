#pragma once

#define TILE_WIDTH 128
#define TILE_HEIGHT 64

#define TILE_NUM 32
#define TREE_NUM 36
#define TANGERIN_TREE_NUM 15
#define STONE_NUM 10

class TileMap
{
public:
	TileMap();
	TileMap(LPDIRECT3DDEVICE9 pd3dDevice);
	~TileMap();

public:
	Tile* m_pTile[TILE_NUM][TILE_NUM];
	RenderObject* m_pTree[TREE_NUM];
	int nTreeCount;

	RenderObject* m_pTangerin_Tree[TANGERIN_TREE_NUM];
	int nTangerinTreeCount;

	RenderObject* m_pStone[STONE_NUM];

	float m_fTileAngle;

public:
	void InitTileMap(LPDIRECT3DDEVICE9 pd3dDevice);

	void Process();

public:
	void SetSoilTile();
	void SetWaterTile();
	void SetGrassTile();
	void SetTree(LPDIRECT3DDEVICE9 pd3dDevice);
	void SetTengerinTree(LPDIRECT3DDEVICE9 pd3dDevice);
	void SetStone(LPDIRECT3DDEVICE9 pd3dDevice);

public:
	bool IsPointOnTile(Tile* pTile, float x, float y);
};

