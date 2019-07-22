#pragma once
#include "Object.h"
#include "Bullet.h"

#define ADDON_WIDTH 40
#define ADDON_HEIGHT 15
#define ADDON_BULLET 50

class AddOnPlayer
	:public Object
{
public:
	AddOnPlayer();
	AddOnPlayer(LPDIRECT3DTEXTURE9 texture);
	~AddOnPlayer();

	Bullet* pBullet[ADDON_BULLET];

private:
	float fBulletTime;
	int nBulletCount;

public:
	void Create();
	void Update();
	void CreateBullet();
	void Shot();
};

