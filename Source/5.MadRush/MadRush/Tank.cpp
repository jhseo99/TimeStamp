#include "stdafx.h"

Tank::Tank(void)
{
}

Tank::Tank(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	nFrameWidth = width;
	nFrameHeight = height;
	Create();
}

Tank::~Tank(void)
{
}

void Tank::Create()
{
	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = nFrameWidth;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	fSpeed = 0.25f;

	nCurrentShot = 0;
	nCurAbsoluteFrame = 0;

	fWay = 36.0f;

	fHp = 100.0f;

	CreateMissile();
}

void Tank::CreateMissile()
{
	nBulletCount = 72;

	vecBullet.reserve(nBulletCount);

	Bullet* pTemp = NULL;

	for (int i = 0; i < nBulletCount; i++)
	{
		pTemp = new Bullet(OBJMANAGER()->GetTexture(GaBase::TextureID::CIRCLEBULLET), 45, 45, 3.0f);
		vecBullet.push_back(pTemp);
	}
}

void Tank::Shoot(DWORD absoluteFrame)
{
	Hit(100.0f);

	if (bVisible)
	{
		if (absoluteFrame - nCurAbsoluteFrame > 250)
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
}

void Tank::Circle(Bullet* bullet, int num)
{
	bullet->GetDirectVec()->x = cos(2.0 * PI * (num / fWay));
	bullet->GetDirectVec()->y = sin(2.0 * PI * (num / fWay));

	D3DXVec2Normalize(bullet->GetDirectVec(), bullet->GetDirectVec());
}

void Tank::Process()
{
}