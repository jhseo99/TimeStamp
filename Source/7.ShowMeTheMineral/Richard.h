#pragma once
#include "Boss.h"

#define RICHARD_WIDTH 380
#define RICHARD_HEIGHT 360
#define ANI_RICHARD 12

class Richard
	:public Boss
{
public:
	Richard();
	Richard(LPDIRECT3DTEXTURE9 texture);
	~Richard();

	Effect* pLazer;
	Effect* pBombEffect;

private:
	float fLazerTime;

	RECT rtAni[ANI_RICHARD];
	float fAniTime;
	int nAniCount;
	int nCurrentAni;

public:
	void Create();
	void Update(Player* pPlayer);
	void Shot();
	void SetAniRect();
	void AniRichard();
};

