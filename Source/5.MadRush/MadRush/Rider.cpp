#include "stdafx.h"

Rider::Rider(void)
{
}

Rider::Rider(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	nFrameWidth = width;
	nFrameHeight = height;
	Create();
}

Rider::~Rider(void)
{
}

void Rider::Create()
{
	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = nFrameWidth;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	fSpeed = 1.5f;
	nCurrentShot = 0;
	nCurAbsoluteFrame = 0;

	fHp = 10.0f;

	CreateMissile();
}

void Rider::CreateMissile()
{
	nBulletCount = 10;

	vecBullet.reserve(nBulletCount);

	Bullet* pTemp = NULL;

	for (int i = 0; i < nBulletCount; i++)
	{
		pTemp = new Bullet(OBJMANAGER()->GetTexture(GaBase::TextureID::DIRECTBULLET), 20, 20, 5.0f);
		vecBullet.push_back(pTemp);
	}
}

void Rider::Shoot(DWORD absoluteFrame)
{
	Hit(10.0f);

	if (bVisible && vPosition.y < 200)
	{
		if (absoluteFrame - nCurAbsoluteFrame > 30)
		{
			vecBullet[nCurrentShot]->SetVisible(true);
			vecBullet[nCurrentShot]->SetShoot(true);
			vecBullet[nCurrentShot]->SetFirePos((vPosition.x + nFrameWidth / 2) - 10, vPosition.y);

			nCurrentShot++;

			if (nCurrentShot > nBulletCount - 1)
			{
				nCurrentShot = 0;
			}
			nCurAbsoluteFrame = absoluteFrame;
		}
	}
}

void Rider::Process()
{
}