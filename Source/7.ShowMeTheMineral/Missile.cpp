#include "DXUT.h"
#include "Missile.h"
#include "GaTimer.h"

Missile::Missile()
{
}

Missile::Missile(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

Missile::~Missile()
{
}

void Missile::Update(Player* pPlayer)
{
	if (bVisible)
	{
		Move();
		if (bHit)
		{
			pPlayer->SetGunState(Player::GunState::MISSILE);
			pPlayer->SetGunTime(GATIMER()->GetTimer());

			bHit = false;
			bVisible = false;
		}
	}
}