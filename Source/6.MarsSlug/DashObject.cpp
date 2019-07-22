#include "DXUT.h"
#include "DashObject.h"


DashObject::DashObject()
{
	InitDashObject();
	ZeroMemory(&vDirection, sizeof(vDirection));
}


DashObject::~DashObject()
{
}

void DashObject::InitDashObject()
{
	SetSpeedX(0);
	SetSpeedY(0);
	pEffect = new Effect;
	pEffect->SetAniEffect(250, 250, 5, 2);
}

void DashObject::Move()
{
	vPosition.x += vDirection.x * fSpeed;
	vPosition.y += vDirection.y * fSpeed;
	if (vPosition.x <= 0 - rtSize.right)
	{
		bVisible = false;
	}
}

void DashObject::Dash(Player* pPlayer)
{
	vDirection.x = pPlayer->GetPosition()->x - vPosition.x;
	vDirection.y = pPlayer->GetPosition()->y - vPosition.y;

	D3DXVec3Normalize(&vDirection, &vDirection);
}

void DashObject::Die()
{
	if (bDie)
	{
		pEffect->SetPosition(vPosition);
		pEffect->SetVisible(true);
		pEffect->AniEffect(10);
	}
	if (pEffect->GetFinish())
	{
		bDie = false;
		pEffect->SetFinish(false);
	}
}