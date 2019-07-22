#include "DXUT.h"
#include "MissileThree.h"
#include "GaTimer.h"

MissileThree::MissileThree()
{
}

MissileThree::MissileThree(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

MissileThree::~MissileThree()
{
}

void MissileThree::Update(Player* pPlayer)
{
	if (bVisible)
	{
		Move();
		if (bHit)
		{
			pPlayer->SetGunState(Player::GunState::MISSILE_THREE);
			pPlayer->SetGunTime(GATIMER()->GetTimer());

			bHit = false;
			bVisible = false;
		}
	}
}