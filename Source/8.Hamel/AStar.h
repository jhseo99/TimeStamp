#pragma once
#include<deque>
class AStar
{
public:
	AStar();
	~AStar();

public:
	Tile* m_pTileSet[TILE_NUM][TILE_NUM];

	std::vector <Tile*> m_vecOpenNode;
	std::vector <Tile*> m_vecCloseNode;
	std::deque <Tile*> m_deqBestPath;

public:
	void Init();
	void PathFind(Tile* pStartPos, Tile* pGoalPos);

	int SetMoveValue(Tile* pTileA, Tile* pTileB);

	bool IsGoal(int x, int y);
	void CreateChildNode(int curX, int curY, int startX, int startY, int goalX, int goalY);

	bool IsSameOpenNode(Tile* pTile);
	bool IsSameCloseNode(Tile* pTile);

	void SetBestPath(Tile* pStart, Tile* pGoal);
	bool IsAdjacent(int x1, int x2, int y1, int y2);
};

