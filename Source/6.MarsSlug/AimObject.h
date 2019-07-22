#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "Effect.h"

#define MAX_BULLET 50

class AimObject
	:public Enemy
{
public:
	AimObject();
	~AimObject();

protected:
	Bullet* pBullet[MAX_BULLET];
	float fLastBullet;
	int nCurBullet;

	Effect* pEffect;

	D3DXVECTOR3 vDirection;

	float lastEffect;

public:
	void InitAimObject();
	void CreateBullet(int width, int height);
	void Aim(Player* pPlayer);
	void Shot(Player* pPlayer, float fFirePosX, float fFirePosY, float fTime);
	void Die();

public:
	Bullet* GetBullet(int num) { return pBullet[num]; }
	Effect* GetEffect() { return pEffect; }
};

