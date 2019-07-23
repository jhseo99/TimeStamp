#pragma once
#include "Item.h"

class HpUp
	:public Item
{
public:
	HpUp();
	HpUp(LPDIRECT3DTEXTURE9 texture);
	~HpUp();

public:
	virtual void Update(Player* pPlayer);
};

