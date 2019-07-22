#pragma once
class Tile
	:public RenderObject
{
public:
	Tile();
	~Tile();

	enum TileID{BASIC1, BASIC2, WATER, SAND, GRASS, BRIDGE, TREE, TANGERIN_TREE, STONE};

public:
	int m_nTileX;
	int m_nTileY;

	bool m_bHit;
	bool m_bMovable;
	TileID m_enId;

	Tile* m_pParentNode;
	int m_nGValue;
	int m_nHValue;
	int m_nFValue;

public:
	void Init();

	void SetTileProperty();	
	void SetTileID(TileID id_) { m_enId = id_; }
};

