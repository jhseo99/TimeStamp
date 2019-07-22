#include "DXUT.h"
#include "GaBase.h"


CollisionObject::CollisionObject()
{
	InitCollision();
}


CollisionObject::~CollisionObject()
{
}

void CollisionObject::InitCollision()
{
	ZeroMemory(&rtCollision, sizeof(rtCollision));
	bHit = false;
}