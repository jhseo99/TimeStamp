#include "DXUT.h"
#include "GaBase.h"


MoveObject::MoveObject()
{
	Init();
}


MoveObject::~MoveObject()
{
}

void MoveObject::Init()
{
	m_enDirection = Direction::DOWN;
	m_fSpeed = 0.0f;
	m_vDirection.x = 0.0f;
	m_vDirection.y = 0.0f;
	m_bMove = false;
	m_deqMoveTile.clear();
}

void MoveObject::SetDirectVec()
{
	switch (m_enDirection)
	{
	case Direction::UP:
		m_vDirection.x = 0.0f;
		m_vDirection.y = -1.0f;
		break;
	case Direction::DOWN:
		m_vDirection.x = 0.0f;
		m_vDirection.y = 1.0f;
		break;
	case Direction::LEFT:
		m_vDirection.x = -1.0f;
		m_vDirection.y = 0.0f;
		break;
	case Direction::RIGHT:
		m_vDirection.x = 1.0f;
		m_vDirection.y = 0.0f;
		break;
	case Direction::LUP:
		m_vDirection.x = -1.0f;
		m_vDirection.y = -0.5f;
		break;
	case Direction::RUP:
		m_vDirection.x = 1.0f;
		m_vDirection.y = -0.5f;
		break;
	case Direction::LDWON:
		m_vDirection.x = -1.0f;
		m_vDirection.y = 0.5f;
		break;
	case Direction::RDOWN:
		m_vDirection.x = 1.0f;
		m_vDirection.y = 0.5f;
		break;
	default:
		break;
	}

	D3DXVec2Normalize(&m_vDirection, &m_vDirection);
}

void MoveObject::Move()
{
	if (m_deqMoveTile.empty() == false)
	{
		Tile* tile = m_deqMoveTile.back();
		D3DXVECTOR2 vDiff;
		vDiff.x = tile->m_vPosition.x - m_vPosition.x;
		vDiff.y = tile->m_vPosition.y - (m_vPosition.y + 64);
		float fDistance = D3DXVec2Length( &vDiff );
		D3DXVec2Normalize(&vDiff, &vDiff);
		m_vPosition.x += vDiff.x * m_fSpeed;
		m_vPosition.y += vDiff.y * m_fSpeed;

		if (fDistance <= 3)
		{
			m_deqMoveTile.pop_back();
		}
	}
	
}

void MoveObject::SetMovePath(std::deque<Tile*> deqTile)
{
	m_deqMoveTile = deqTile;
}