#include "DXUT.h"
#include "AimObject.h"


AimObject::AimObject()
{
	InitAimObject();
	ZeroMemory(&vDirection, sizeof(vDirection));
}


AimObject::~AimObject()
{
}

void AimObject::InitAimObject()
{
	fLastBullet = 0;
	nCurBullet = 0;
	pEffect = new Effect;
	pEffect->SetAniEffect(220, 220, 5, 2);
}

void AimObject::Shot(Player* pPlayer, float fFirePosX, float fFirePosY, float fTime)
{
	D3DXVECTOR3 vFirePos;

	if (DXUTGetTime() - fLastBullet > fTime && vPosition.x >= (SCREEN_WIDTH / 2))
	{
		pBullet[nCurBullet]->SetShot(true);
		pBullet[nCurBullet]->SetVisible(true);

		vFirePos.x = fFirePosX;
		vFirePos.y = fFirePosY;
		vFirePos.z = 0;

		pBullet[nCurBullet]->SetPosition(vFirePos);
		pBullet[nCurBullet]->SetSpeedX(5.0f);
		pBullet[nCurBullet]->SetSpeedY(5.0f);

		Aim(pPlayer);

		nCurBullet++;

		fLastBullet = DXUTGetTime();
	}

	if (nCurBullet >= MAX_BULLET)
	{
		nCurBullet = 0;
	}
}

void AimObject::Aim(Player* pPlayer)
{
	vDirection.x = pPlayer->GetPosition()->x - pBullet[nCurBullet]->GetPosition()->x;
	vDirection.y = pPlayer->GetPosition()->y - pBullet[nCurBullet]->GetPosition()->y;

	D3DXVec3Normalize(&vDirection, &vDirection);

	pBullet[nCurBullet]->SetDirection(vDirection);
}

void AimObject::CreateBullet(int width, int height)
{
	RECT rt;
	rt.left = 0;
	rt.right = width;
	rt.top = 0;
	rt.bottom = height;

	for (int i = 0; i < MAX_BULLET; i++)
	{
		pBullet[i] = new Bullet;
		pBullet[i]->SetSpeedX(25.0f);
		pBullet[i]->SetSpeedY(25.0f);
		pBullet[i]->SetGradiant(0);
		pBullet[i]->SetRect(rt);
	}
}

void AimObject::Die()
{
	if (bDie)
	{
		pEffect->SetPosition(vPosition);
		pEffect->SetVisible(true);
		pEffect->AniEffect(10);
	}
	if (pEffect->GetFinish())
	{
		pEffect->SetFinish(false);
		bDie = false;
	}
}