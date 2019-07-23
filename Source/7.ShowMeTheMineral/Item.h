#pragma once
#include "Object.h"
#include "Player.h"

class Item
	:public Object
{
public:
	Item();
	~Item();

public:
	virtual void Create();
	virtual void Respawn();
	virtual void Update(Player* pPlayer);
	virtual void Move();
};

