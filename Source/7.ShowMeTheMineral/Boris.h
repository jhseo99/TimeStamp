#pragma once
#include "Boss.h"
#include "Player.h"
#include "DirectBullet.h"
#include "Effect.h"

#define BORIS_WIDTH 320
#define BORIS_HEIGHT 400
#define BORIS_MAX_BULLET 400
#define ANI_BORIS 20

class Boris
	:public Boss
{
public:
	Boris();
	Boris(LPDIRECT3DTEXTURE9 texture);
	~Boris();

	DirectBullet* pBullet[BORIS_MAX_BULLET];
	Effect* pBombEffect;

private:
	float fBulletRespawn;
	float fBulletTime;
	int nBulletCount;
	int nBulletCheck;

	RECT rtAni[ANI_BORIS];
	float fAniTime;
	int nAniCount;
	int nCurrentAni;

public:
	void Create();
	void Update(Player* pPlayer);
	void CreateBullet();
	void Shot();
	void CircleRespawn(DirectBullet* pBullet, int num);
	void SetAniRect();
	void AniBoris();
};

