#pragma once
#include "Enemy.h"
#include "AimBullet.h"
#include "Effect.h"

#define JOHN_WIDTH 70
#define JOHN_HEIGHT 110
#define JOHN_MAX_BULLET 20
#define ANI_MOVE 3

class John
	:public Enemy
{
public:
	John();
	John(LPDIRECT3DTEXTURE9 texture);
	~John();

	AimBullet* pBullet[JOHN_MAX_BULLET];

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