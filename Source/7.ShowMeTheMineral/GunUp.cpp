#include "DXUT.h"
#include "GunUp.h"
#include "GaTimer.h"

GunUp::GunUp()
{
}

GunUp::GunUp(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

GunUp::~GunUp()
{
}

void GunUp::Update(Player* pPlayer)
{
	if (bVisible)
	{
		Move();
		if (bHit)
		{
			if (pPlayer->GetGunLevel() < 3)
			{
				pPlayer->SetGunLevel(pPlayer->GetGunLevel() + 1);
			}
			bHit = false;
			bVisible = false;
		}
	}
}