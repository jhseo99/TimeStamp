#include "stdafx.h"

Buzzard::Buzzard(void)
{
}

Buzzard::Buzzard(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	nFrameWidth = width;
	nFrameHeight = height;
	Create();
}

Buzzard::~Buzzard(void)
{
}

void Buzzard::Create()
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

	fHp = 50.0f;

	CreateMissile();
}

void Buzzard::CreateMissile()
{
	nBulletCount = 30;

	vecBullet.reserve(nBulletCount);

	Bullet* pTemp = NULL;

	for (int i = 0; i < nBulletCount; i++)
	{
		pTemp = new Bullet(OBJMANAGER()->GetTexture(GaBase::TextureID::NWAYBULLET), 30, 30, 3.0f);
		vecBullet.push_back(pTemp);
	}
}

void Buzzard::Shoot(DWORD absoluteFrame)
{
	Hit(50.0f);

	if (bVisible && vPosition.y < 500)
	{
		if (absoluteFrame - nCurAbsoluteFrame > 150)
		{
			for (int i = 0; i < (int)fWay; i++)
			{
				vecBullet[nCurrentShot]->SetVisible(true);
				vecBullet[nCurrentShot]->SetShoot(true);
				vecBullet[nCurrentShot]->SetFirePos((vPosition.x + nFrameWidth / 2) - 15, vPosition.y + 50);
				
				nWay(vecBullet[nCurrentShot], i);
			
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

void Buzzard::nWay(Bullet* bullet, int num)
{
	bullet->GetDirectVec()->x = cos(PI * (num / fWay));
	bullet->GetDirectVec()->y = sin(PI * (num / fWay) + (10.0 * (PI / 180)));

	D3DXVec2Normalize(bullet->GetDirectVec(), bullet->GetDirectVec());
}

void Buzzard::Process()
{
}