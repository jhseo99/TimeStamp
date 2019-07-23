#include "DXUT.h"
#include "SplitBullet.h"


SplitBullet::SplitBullet()
{
}

SplitBullet::SplitBullet(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	Create(width, height);
}

SplitBullet::~SplitBullet()
{
}

void SplitBullet::Create(int width, int height)
{
	SetRect(0, width, 0, height);

	fSpeed = 0.0f;
	fAngle = 0.0f;
	bShot = false;

	fSplitTime = 0.0f;
	bSplit = false;

	bVisible = false;

	for (int i = 0; i < SPLIT_MAX_BULLET; i++)
	{
		pBullet[¤Á]
	}

	ZeroMemory(&vDirect, sizeof(vDirect));
}

void SplitBullet::Split()
{

}

void SplitBullet::CircleRespawn(DirectBullet* pBullet, int num)
{

}