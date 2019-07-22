#include "DXUT.h"
#include "SpeedUp.h"
#include "GaTimer.h"

SpeedUp::SpeedUp()
{
}

SpeedUp::SpeedUp(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

SpeedUp::~SpeedUp()
{
}

void SpeedUp::Update(Player* pPlayer)
{
	if (bVisible)
	{
		Move();
		if (bHit)
		{
			if (pPlayer->GetSpeed() < 8)
			{
				pPlayer->SetSpeed(pPlayer->GetSpeed() + 1);
			}
			bHit = false;
			bVisible = false;
		}
	}
}