#pragma once
#include "Enemy.h"
#include "Object.h"

#define MAX_BOSS_HP 100

class Boss
	:public Enemy
{
public:
	Boss();
	~Boss();

	enum MoveState{LEFT, RIGHT, UP, DOWN};

	Object* pHpBar;
	Object* pHp[MAX_BOSS_HP];

protected:
	MoveState moveState;
	float fMoveRespawn;
	float fMoveTime;

	bool bRespawn;
	bool bRandMove;

public:
	void Respawn(float hp);
	void Move();

	bool GetRespawn() { return bRespawn; }
	void SetRespawn(bool respawn) { bRespawn = respawn; }
};

