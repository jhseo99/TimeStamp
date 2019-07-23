#include "stdafx.h"

Truck::Truck(void)
{
}

Truck::Truck(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	nFrameWidth = width;
	nFrameHeight = height;
	Create();
}

Truck::~Truck(void)
{
}

void Truck::Create()
{
	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = nFrameWidth;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	fSpeed = 0.4f;
	nCurrentShot = 0;
	nCurAbsoluteFrame = 0;

	fHp = 70.0f;

	CreateMissile();
}

void Truck::CreateMissile()
{
	nBulletCount = 50;

	vecBullet.reserve(nBulletCount);

	Bullet* pTemp = NULL;

	for (int i = 0; i < nBulletCount; i++)
	{
		pTemp = new Bullet(OBJMANAGER()->GetTexture(GaBase::TextureID::AIMBULLET2), 20, 20, 4.0f);
		vecBullet.push_back(pTemp);
	}
}

void Truck::Shoot(DWORD absoluteFrame)
{
	Hit(70.0f);

	if (bVisible && vPosition.y < 400)
	{
		if (absoluteFrame - nCurAbsoluteFrame > 20)
		{
			vecBullet[nCurrentShot]->SetVisible(true);
			vecBullet[nCurrentShot]->SetShoot(true);
			vecBullet[nCurrentShot]->SetFirePos((vPosition.x + nFrameWidth / 2) - 5, vPosition.y);

			Aim();

			nCurrentShot++;

			if (nCurrentShot > nBulletCount - 1)
			{
				nCurrentShot = 0;
			}
			nCurAbsoluteFrame = absoluteFrame;
		}
	}
}

void Truck::Aim()
{
	vecBullet[nCurrentShot]->SetRandNum(GATIMER()->GetRand(2, 1));

	if (vecBullet[nCurrentShot]->GetRandNum() == 1)
	{
		vecBullet[nCurrentShot]->GetDirectVec()->x = OBJMANAGER()->GetPlayer1()->GetPosition()->x - vPosition.x;
		vecBullet[nCurrentShot]->GetDirectVec()->y = OBJMANAGER()->GetPlayer1()->GetPosition()->y - vPosition.y;
	}
	else if (vecBullet[nCurrentShot]->GetRandNum() == 2)
	{
		vecBullet[nCurrentShot]->GetDirectVec()->x = OBJMANAGER()->GetPlayer2()->GetPosition()->x - vPosition.x;
		vecBullet[nCurrentShot]->GetDirectVec()->y = OBJMANAGER()->GetPlayer2()->GetPosition()->y - vPosition.y;
	}

	D3DXVec2Normalize(vecBullet[nCurrentShot]->GetDirectVec(), vecBullet[nCurrentShot]->GetDirectVec());
}

void Truck::Process()
{
}