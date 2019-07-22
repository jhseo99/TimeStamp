#pragma once
#include "Item.h"

class AimMissile
	:public Item
{
public:
	AimMissile();
	AimMissile(LPDIRECT3DTEXTURE9 texture);
	~AimMissile();

public:
	virtual void Update(Player* pPlayer);
};

