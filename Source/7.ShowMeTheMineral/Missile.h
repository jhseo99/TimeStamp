#pragma once
#include "Item.h"

class Missile
	:public Item
{
public:
	Missile();
	Missile(LPDIRECT3DTEXTURE9 texture);
	~Missile();

public:
	virtual void Update(Player* pPlayer);
};

