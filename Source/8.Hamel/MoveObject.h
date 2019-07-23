#pragma once
#include <deque>
#include "Tile.h"
class MoveObject
	:public RenderObject
{
public:
	MoveObject();
	~MoveObject();

	enum Direction{ UP, DOWN, LEFT, RIGHT, LUP, RUP, LDWON, RDOWN };
public:
	Direction m_enDirection;

	float m_fSpeed;
	D3DXVECTOR2 m_vDirection;

	bool m_bMove;
	std::deque<Tile*> m_deqMoveTile;
public:
	void Init();
	void SetDirectVec();

	virtual void Move();
	void SetMovePath(std::deque<Tile*> deqTile);
};

