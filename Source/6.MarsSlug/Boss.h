#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Effect.h"

#define PI 3.141592

#define BOSS_WIDTH 340
#define BOSS_HEIGHT 340

#define MAX_BULLET 48

class Boss
	:public Enemy
{
public:
	Boss();
	~Boss();

private:
	Bullet* pBullet[MAX_BULLET];
	float fLastBullet;
	int nCurBullet;

	Effect* pEffect;

	float lastEffect;

public:
	void InitBoss();
	void CreateBullet(int width, int height);
	void Shot(float nWay);
	void CircleBullet(Bullet* pBullet, int num, float nWay);
	void Die();
	void Process(float nWay);

public:
	Bullet* GetBullet(int num) { return pBullet[num]; }
	Effect* GetEffect() { return pEffect; }
};

