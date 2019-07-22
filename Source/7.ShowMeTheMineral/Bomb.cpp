#include "DXUT.h"
#include "Bomb.h"
#include "GaTimer.h"

Bomb::Bomb()
{
}

Bomb::Bomb(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

Bomb::~Bomb()
{
}

void Bomb::Update(Player* pPlayer)
{
	if (bVisible)
	{
		Move();
		if (bHit)
		{
			pPlayer->SetBombCount(pPlayer->GetBombCount() + 1);

			bHit = false;
			bVisible = false;
		}
	}
}