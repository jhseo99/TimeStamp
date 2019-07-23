#pragma once
#include "Item.h"

class AddOnPlus
	:public Item
{
public:
	AddOnPlus();
	AddOnPlus(LPDIRECT3DTEXTURE9 texture);
	~AddOnPlus();

public:
	virtual void Update(Player* pPlayer);
};

