#pragma once
#include "Enemy.h"
#include "AimBullet.h"
#include "Effect.h"

#define JAMES_WIDTH 90
#define JAMES_HEIGHT 50
#define JAMES_MAX_BULLET 10
#define ANI_MOVE 4

class James
	:public Enemy
{
public:
	James();
	James(LPDIRECT3DTEXTURE9 texture);
	~James();

	AimBullet* pBullet[JAMES_MAX_BULLET];

	Effect* pBombEffect;

private:
	float fBulletRespawn;
	float fBulletTime;
	int nBulletCount;
	int nBulletCheck;

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

