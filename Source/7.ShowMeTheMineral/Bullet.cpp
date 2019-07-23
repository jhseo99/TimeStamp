#include "DXUT.h"
#include "Bullet.h"


Bullet::Bullet()
{
}

Bullet::Bullet(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	Create(width, height);
}

Bullet::~Bullet()
{
}

void Bullet::Create(int width, int height)
{
	SetRect(0, width, 0, height);
	
	fSpeed = 0.0f;
	fAngle = 0.0f;
	bShot = false;

	bVisible = false;
}

void Bullet::Shot()
{
	if (bShot)
	{
		vPosition.x += fSpeed;
		vPosition.y += fAngle * fSpeed;
	}
	if (bHit)
	{
		bVisible = false;
		bHit = false;
	}
}