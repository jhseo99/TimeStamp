#pragma once
#include "Item.h"

class SpeedUp
	:public Item
{
public:
	SpeedUp();
	SpeedUp(LPDIRECT3DTEXTURE9 texture);
	~SpeedUp();

public:
	virtual void Update(Player* pPlayer);
};

