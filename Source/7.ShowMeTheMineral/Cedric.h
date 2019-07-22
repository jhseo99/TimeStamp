#pragma once
#include "Boss.h"
#include "DirectBullet.h"

#define CEDRIC_WIDTH 490
#define CEDRIC_HEIGHT 370
#define CEDRIC_SPLIT_BULLET 8
#define CEDRIC_MAX_BULLET 320
#define ANI_CEDRIC 10

class Cedric
	:public Boss
{
public:
	Cedric();
	Cedric(LPDIRECT3DTEXTURE9 texture);
	~Cedric();

	DirectBullet* pSplitBullet[CEDRIC_MAX_BULLET];
	DirectBullet* pBullet[CEDRIC_MAX_BULLET];

	Effect* pBombEffect;

private:
	float fSplitBulletTime;
	float fSplitFireTime;
	int nSplitBulletCount;
	float fBulletTime;
	int nBulletCount;
	bool bSplit;

	RECT rtAni[ANI_CEDRIC];
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
	void AniCedric();
};

