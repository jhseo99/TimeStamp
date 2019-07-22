#include "DXUT.h"
#include "AddOnPlus.h"
#include "GaTimer.h"

AddOnPlus::AddOnPlus()
{
}

AddOnPlus::AddOnPlus(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

AddOnPlus::~AddOnPlus()
{
}

void AddOnPlus::Update(Player* pPlayer)
{
	if (bVisible)
	{
		Move();
		if (bHit)
		{
			if (pPlayer->GetAddonLevel() < 2)
			{
				pPlayer->SetAddonLevel(pPlayer->GetAddonLevel() + 1);
			}
			bHit = false;
			bVisible = false;
		}
	}
}