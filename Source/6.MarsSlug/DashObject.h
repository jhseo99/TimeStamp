#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Effect.h"

class DashObject
	:public Enemy
{
public:
	DashObject();
	~DashObject();

protected:
	D3DXVECTOR3 vDirection;
	float fSpeed;

	Effect* pEffect;

	float lastEffect;

public:
	void InitDashObject();
	void Dash(Player* pPlayer);
	void Move();
	void Die();

public:
	float GetSpeed() { return fSpeed; };
	void SetSpeed(float speed) { fSpeed = speed; };

	Effect* GetEffect() { return pEffect; }
};

