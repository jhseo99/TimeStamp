#pragma once
#include "Item.h"

class Bomb
	:public Item
{
public:
	Bomb();
	Bomb(LPDIRECT3DTEXTURE9 texture);
	~Bomb();

public:
	virtual void Update(Player* pPlayer);
};

