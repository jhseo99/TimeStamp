#pragma once
#include "Item.h"

class GunUp
	:public Item
{
public:
	GunUp();
	GunUp(LPDIRECT3DTEXTURE9 texture);
	~GunUp();

public:
	virtual void Update(Player* pPlayer);
};

