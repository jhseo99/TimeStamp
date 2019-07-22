#pragma once
#include "Object.h"
#include "Player.h"

class Enemy
	:public Object
{
public:
	Enemy();
	~Enemy();

protected:
	float fSpeed;
	bool bHitAni;
	float fHitTime;
	bool bDie;

public:
	void Respawn(float hp, float speed);
	void StraightMove();
	void HitSystem(Player* pPlayer);

	bool GetDie() { return bDie; }
	void SetDie(bool die) { bDie = die; }
};

