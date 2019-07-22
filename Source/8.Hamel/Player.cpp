#include "DXUT.h"
#include "GaBase.h"


Player::Player()
{
	Init();
}


Player::~Player()
{
}

void Player::Init()
{
	m_nPlayerX = 31;
	m_nPlayerY = 31;
	m_nGoalX = 0;
	m_nGoalY = 0;
	m_fSpeed = 3.0f;
	m_fFoodGauge = 100.0f;
	m_fWaterGauge = 100.0f;
	m_fSleepGauge = 100.0f;
}

void Player::Process(TileMap* pTileMap)
{
	SetDirection();
	SetDirectVec();

	for (int i = 0; i < TILE_NUM; i++)
	{
		for (int j = 0; j < TILE_NUM; j++)
		{
			if (pTileMap->IsPointOnTile(pTileMap->m_pTile[i][j], m_vPosition.x + 64, m_vPosition.y + 100))
			{
				m_nPlayerX = i;
				m_nPlayerY = j;
			}
		}
	}

	Move();
}

void Player::SetDirection()
{
	if (m_nGoalX < m_nPlayerX &&
		m_nGoalY == m_nPlayerY)
	{
		m_enDirection = Direction::LUP;
	}
	else if (m_nGoalX > m_nPlayerX &&
			 m_nGoalY == m_nPlayerY)
	{
		m_enDirection = Direction::RDOWN;
	}
	else if (m_nGoalY < m_nPlayerY &&
			 m_nGoalX == m_nPlayerX)
	{
		m_enDirection = Direction::RUP;
	}
	else if (m_nGoalY > m_nPlayerY &&
			 m_nGoalX == m_nPlayerX)
	{
		m_enDirection = Direction::LDWON;
	}
	else if (m_nGoalX < m_nPlayerX &&
	 		 m_nGoalY > m_nPlayerY)
	{
		m_enDirection = Direction::LEFT;
	}
	else if (m_nGoalX > m_nPlayerX &&
			 m_nGoalY > m_nPlayerY)
	{
		m_enDirection = Direction::RIGHT;
	}
	else if (m_nGoalX < m_nPlayerX &&
			 m_nGoalY < m_nPlayerY)
	{
		m_enDirection = Direction::UP;
	}
	else if (m_nGoalX > m_nPlayerX &&
			 m_nGoalY > m_nPlayerY)
	{
		m_enDirection = Direction::DOWN;
	}
}
