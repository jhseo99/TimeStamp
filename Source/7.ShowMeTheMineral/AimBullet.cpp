#include "DXUT.h"
#include "AimBullet.h"


AimBullet::AimBullet()
{
}

AimBullet::AimBullet(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	Create(width, height);
}

AimBullet::~AimBullet()
{
}

void AimBullet::Create(int width, int height)
{
	SetRect(0, width, 0, height);

	bAim = false;
	fSpeed = 0.0f;
	fAngle = 0.0f;
	bShot = false;

	bVisible = false;

	vDirect.x = 1.0f;
	vDirect.y = 0.0f;
	vDirect.z = 0.0f;
}

void AimBullet::Shot()
{
	if (bShot)
	{
		if (bAim)
		{
			vPosition.x += vDirect.x * fSpeed;
			vPosition.y += vDirect.y * fSpeed;
		}
		if (!bAim)
		{
			vPosition.x += fSpeed;
		}
	}
	if (bHit)
	{
		bVisible = false;
		bAim = false;
		bHit = false;
	}
}

void AimBullet::Aim(Object* pObject)
{
	if (bShot && !bAim)
	{
		if (vPosition.x + 300 >= pObject->GetPosition()->x &&
			vPosition.x < pObject->GetPosition()->x &&
			pObject->GetVisible())
		{
			pTarget = pObject;
			bAim = true;
		}
	}
	if (bAim)
	{
		vDirect.x = pTarget->GetCenterPos()->x + 20 - vPosition.x;
		vDirect.y = pTarget->GetCenterPos()->y + 20 - vPosition.y;
		vDirect.z = 0.0f;

		D3DXVec3Normalize(&vDirect, &vDirect);

		if (!pTarget->GetVisible())
		{
			bAim = false;
		}
	}
}