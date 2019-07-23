#include "DXUT.h"
#include "GaBase.h"


AStar::AStar()
{
	Init();
}


AStar::~AStar()
{
}

void AStar::Init()
{
	m_vecOpenNode.clear();
	m_vecCloseNode.clear();
	m_deqBestPath.clear();
}

void AStar::PathFind(Tile* pStartPos, Tile* pGoalPos)
{
	Tile* pStart = pStartPos;
	Tile* pGoal = pGoalPos;

	m_vecOpenNode.clear();
	m_vecCloseNode.clear();

	pStart->m_nGValue = SetMoveValue(pStart, pGoal);
	pStart->m_nHValue = 0;
	pStart->m_nFValue = pStart->m_nGValue + pStart->m_nHValue;

	pGoal->m_nGValue = 0;
	pGoal->m_nHValue = SetMoveValue(pStart, pGoal);
	pGoal->m_nFValue = pGoal->m_nGValue + pGoal->m_nHValue;

	while (!IsSameCloseNode(pGoal))
	{
		if (m_vecOpenNode.size() == 0 && m_vecCloseNode.size() == 0)
		{
			CreateChildNode(pStart->m_nTileX, pStart->m_nTileY, pStart->m_nTileX, pStart->m_nTileY, pGoal->m_nTileX, pGoal->m_nTileY);
			m_vecCloseNode.push_back(pStart);
		}
		else
		{
			Tile* pMinTile = NULL;
			for (int i = 0; i < m_vecOpenNode.size(); i++)
			{
				if (pMinTile == NULL)
				{
					pMinTile = m_vecOpenNode[i];
				}
				if (m_vecOpenNode[i]->m_nFValue < pMinTile->m_nFValue)
				{
					pMinTile = m_vecOpenNode[i];
				}
				else if (m_vecOpenNode[i]->m_nFValue == pMinTile->m_nFValue &&
						 m_vecOpenNode[i]->m_nHValue < pMinTile->m_nHValue)
				{
					pMinTile = m_vecOpenNode[i];
				}
			}

			CreateChildNode(pMinTile->m_nTileX, pMinTile->m_nTileY, pStart->m_nTileX, pStart->m_nTileY, pGoal->m_nTileX, pGoal->m_nTileY);


			bool bErase = true;
			while (bErase == true)
			{
				bErase = false;
				for (int i = 0; i < m_vecOpenNode.size(); i++)
				{
					if (m_vecOpenNode[i] == pMinTile)
					{
						pMinTile = m_vecOpenNode[i];
						break;
					}
				}

				for (int i = 0; i < m_vecOpenNode.size(); i++)
				{
					if (m_vecOpenNode[i] == pMinTile)
					{
						bErase = true;
						m_vecOpenNode.erase(m_vecOpenNode.begin() + i);
						break;
					}
				}
			}

			m_vecCloseNode.push_back(pMinTile);
		}
	}
	m_deqBestPath.clear();
	//m_vecCloseNode.push_back(pGoal);
	SetBestPath(pStart, pGoal);
	m_deqBestPath.push_back(pStart);
	
	return;
}

int AStar::SetMoveValue(Tile* pTileA, Tile* pTileB)
{
	int result;

	result = abs(pTileA->m_nTileX - pTileB->m_nTileX) + abs(pTileA->m_nTileY - pTileB->m_nTileY);

	return result;
}

bool AStar::IsGoal(int x, int y)
{
	for (int i = 0; i < m_vecOpenNode.size(); i++)
	{
		if (m_vecOpenNode[i]->m_nTileX == x &&
			m_vecOpenNode[i]->m_nTileY == y)
		{
			return true;
		}
	}
	return false;
}

void AStar::CreateChildNode(int curX, int curY, int startX, int startY, int goalX, int goalY)
{
	std::vector<Tile*> vecChildNode;
	vecChildNode.clear();

	if (curX != 31)
	{
		vecChildNode.push_back(m_pTileSet[curX + 1][curY]);
	}
	if (curX != 0)
	{
		vecChildNode.push_back(m_pTileSet[curX - 1][curY]);
	}
	if (curY != 31)
	{
		vecChildNode.push_back(m_pTileSet[curX][curY + 1]);
	}
	if (curY != 0)
	{
		vecChildNode.push_back(m_pTileSet[curX][curY - 1]);
	}

	for (int i = 0; i < vecChildNode.size(); i++)
	{
		vecChildNode[i]->m_nGValue = SetMoveValue(vecChildNode[i], m_pTileSet[goalX][goalY]);
		vecChildNode[i]->m_nHValue = SetMoveValue(m_pTileSet[startX][startY], vecChildNode[i]);
		vecChildNode[i]->m_nFValue = vecChildNode[i]->m_nGValue + vecChildNode[i]->m_nHValue;

		if (vecChildNode[i]->m_bMovable &&
			!IsSameCloseNode(vecChildNode[i]))
		{
			for (int j = 0; j < m_vecOpenNode.size(); j++)
			{
				if (m_vecOpenNode[j] == vecChildNode[i] &&
					m_vecOpenNode[j]->m_nHValue > vecChildNode[i]->m_nHValue)
				{
					m_vecOpenNode[j]->m_nHValue = vecChildNode[i]->m_nHValue;
				}
			}

			if (!IsSameOpenNode(vecChildNode[i]))
			{
				vecChildNode[i]->m_pParentNode = m_pTileSet[curX][curY];
				m_vecOpenNode.push_back(vecChildNode[i]);
			}
		}
	}
}

bool AStar::IsSameOpenNode(Tile* pTile)
{
	for (int i = 0; i < m_vecOpenNode.size(); i++)
	{
		if (m_vecOpenNode[i] == pTile)
		{
			return true;
		}
	}

	return false;
}

bool AStar::IsSameCloseNode(Tile* pTile)
{
	for (int i = 0; i < m_vecCloseNode.size(); i++)
	{
		if (m_vecCloseNode[i] == pTile)
		{
			return true;
		}
	}

	return false;

}

bool AStar::IsAdjacent(int x1, int x2, int y1, int y2)
{
	return 	(::abs(x1 - x2) == 1 && ::abs(y1 - y2) == 0)
		|| (::abs(x1 - x2) == 0 && ::abs(y1 - y2) == 1);
}

void AStar::SetBestPath(Tile* pStart, Tile* pGoal)
{
	if (pStart == pGoal)
	{
		return;
	}
	m_deqBestPath.push_back(pGoal);

	bool bRegisteredStart = false;
	for (int i = 0; i < m_deqBestPath.size(); i++)
	{
		if (pStart->m_nTileX == m_deqBestPath[i]->m_nTileX
			&& pStart->m_nTileY == m_deqBestPath[i]->m_nTileY)
		{
			bRegisteredStart = true;
			break;;
		}
	}
	if (m_deqBestPath.size() >= 1 && bRegisteredStart == true)
	{
		return;
	}//if
	for (int i = 0; i < m_vecCloseNode.size(); i++)
	{
		if (m_vecCloseNode[i] == pGoal && m_vecCloseNode[i]->m_pParentNode != pStart)
		{
			SetBestPath(pStart, m_vecCloseNode[i]->m_pParentNode);
		}
	}

}