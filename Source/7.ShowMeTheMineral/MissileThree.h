#pragma once
#include "Item.h"

class MissileThree
	:public Item
{
public:
	MissileThree();
	MissileThree(LPDIRECT3DTEXTURE9 texture);
	~MissileThree();

public:
	virtual void Update(Player* pPlayer);
};

