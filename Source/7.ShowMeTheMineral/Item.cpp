#include "DXUT.h"
#include "Item.h"


Item::Item()
{
}


Item::~Item()
{
}

void Item::Create()
{
	SetRect(0, 50, 0, 50);
	bHit = false;
	bVisible = true;
}

void Item::Respawn()
{
	vPosition.x = rand() % 900;
	vPosition.y = 0.0f;
	vPosition.z = 0.0f;
	bVisible = true;
	bHit = false;
}

void Item::Update(Player* pPlayer)
{

}

void Item::Move()
{
	SetCollision(0, 50, 0, 50);
	vPosition.y += 2.0f;
	if (vPosition.y >= 580)
	{
		vPosition.y = 580.0f;
	}
}
