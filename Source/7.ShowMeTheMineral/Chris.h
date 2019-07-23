#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Effect.h"

#define CHRIS_WIDTH 160
#define CHRIS_HEIGHT 90
#define CHRIS_MAX_BULLET 20
#define ANI_MOVE 4

class Chris
	:public Enemy
{
public:
	Chris();
	Chris(LPDIRECT3DTEXTURE9 texture);
	~Chris();

	Bullet* pBullet[CHRIS_MAX_BULLET];

	Effect* pBombEffect;

private:
	float fBulletTime;
	int nBulletCount;

	RECT rtMove[ANI_MOVE];
	float fAniMoveTime;
	int nMoveCount;
	int nCurrentMove;

public:
	void Create();
	void Update(Player* pPlayer);
	void Shot(Player* pPlayer);
	void CreateBullet();
	void SetAniRect();
	void AniMove();
};