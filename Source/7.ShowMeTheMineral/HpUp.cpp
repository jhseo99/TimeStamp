#include "DXUT.h"
#include "HpUp.h"


HpUp::HpUp()
{
}

HpUp::HpUp(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

HpUp::~HpUp()
{
}

void HpUp::Update(Player* pPlayer)
{
	if (bVisible)
	{
		Move();
		if (bHit)
		{
			if (pPlayer->GetHp() < 5)
			{
				pPlayer->SetHp(pPlayer->GetHp() + 1);
			}
			bHit = false;
			bVisible = false;
		}
	}
}