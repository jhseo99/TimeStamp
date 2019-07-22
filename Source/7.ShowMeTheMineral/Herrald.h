#pragma once
#include "Boss.h"
#include "Bullet.h"

#define HERRALD_WIDTH 500
#define HERRALD_HEIGHT 290
#define HERRALD_MAX_BULLET 400
#define ANI_HERRALD 12

class Herrald
	:public Boss
{
public:
	Herrald();
	Herrald(LPDIRECT3DTEXTURE9 texture);
	~Herrald();

	Bullet* pBullet1[HERRALD_MAX_BULLET];
	Bullet* pBullet2[HERRALD_MAX_BULLET];

	Effect* pBombEffect;

private:
	float fBulletTime;
	int nBulletCount;

	RECT rtAni[ANI_HERRALD];
	float fAniTime;
	int nAniCount;
	int nCurrentAni;

public:
	void Create();
	void Update(Player* pPlayer);
	void CreateBullet();
	void Shot();
	void SetAniRect();
	void AniHerrald();
};