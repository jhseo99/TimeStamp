#include "DXUT.h"
#include "DirectBullet.h"


DirectBullet::DirectBullet()
{
}

DirectBullet::DirectBullet(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	Create(width, height);
}

DirectBullet::~DirectBullet()
{
}

void DirectBullet::Create(int width, int height)
{
	SetRect(0, width, 0, height);

	fSpeed = 0.0f;
	fAngle = 0.0f;
	bShot = false;

	bVisible = false;

	ZeroMemory(&vDirect, sizeof(vDirect));
}

void DirectBullet::Shot()
{
	if (bShot)
	{
		vPosition.x += vDirect.x * fSpeed;
		vPosition.y += vDirect.y * fSpeed;
	}
	if (bHit)
	{
		bVisible = false;
		bHit = false;
	}
}
