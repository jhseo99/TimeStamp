#include "stdafx.h"

Boss::Boss(void)
{
}

Boss::Boss(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	nFrameWidth = width;
	nFrameHeight = height;
	Create();
}

Boss::~Boss(void)
{
}

void Boss::Create()
{
	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = nFrameWidth;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	fSpeed = 0.5f;

	nCurrentShot = 0;
	nCurAbsoluteFrame = 0;

	fWay = 10.0f;

	fHp = 500.0f;

	CreateMissile();
}

void Boss::CreateMissile()
{
	nBulletCount = 640;

	vecBullet.reserve(nBulletCount);

	Bullet* pTemp = NULL;

	for (int i = 0; i < nBulletCount; i++)
	{
		pTemp = new Bullet(OBJMANAGER()->GetTexture(GaBase::TextureID::BOSSBULLET), 35, 35, 3.5f);
		vecBullet.push_back(pTemp);
	}
}

void Boss::Shoot(DWORD absoluteFrame)
{
	Hit(500.0f);

	if (bVisible)
	{
		if (absoluteFrame - nCurAbsoluteFrame > 25)
		{
			for (int i = 0; i < (int)fWay; i++)
			{
				vecBullet[nCurrentShot]->SetVisible(true);
				vecBullet[nCurrentShot]->SetShoot(true);
				vecBullet[nCurrentShot]->SetFirePos((vPosition.x + nFrameWidth / 2) - 22, vPosition.y + 150);

				Circle(vecBullet[nCurrentShot], i);

				nCurrentShot++;
			}

			if (nCurrentShot > nBulletCount - 1)
			{
				nCurrentShot = 0;
			}

			nCurAbsoluteFrame = absoluteFrame;
		}
	}
	if (vPosition.y > 100)
	{
		vPosition.y = 100;
	}
}

void Boss::Circle(Bullet* bullet, int num)
{
	bullet->GetDirectVec()->x = cos(2.0 * PI * (num / fWay));
	bullet->GetDirectVec()->y = sin(2.0 * PI * (num / fWay));

	D3DXVec2Normalize(bullet->GetDirectVec(), bullet->GetDirectVec());
}

void Boss::Process()
{
}