#include "DXUT.h"
#include "AimMissile.h"
#include "GaTimer.h"

AimMissile::AimMissile()
{
}

AimMissile::AimMissile(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

AimMissile::~AimMissile()
{
}

void AimMissile::Update(Player* pPlayer)
{
	if (bVisible)
	{
		Move();
		if (bHit)
		{
			pPlayer->SetGunState(Player::GunState::MISSILE_AIM);
			pPlayer->SetGunTime(GATIMER()->GetTimer());

			bHit = false;
			bVisible = false;
		}
	}
}