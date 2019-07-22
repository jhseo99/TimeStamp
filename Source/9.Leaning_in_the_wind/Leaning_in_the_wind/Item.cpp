#include "DXUT.h"
#include "GaBase.h"


Item::Item()
{
	Init();
}

Item::Item(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename)
{
	CreateTexture(pd3dDevice, filename);
	Init();
}

Item::~Item()
{
}

void Item::Init()
{
	SetRect(0, 77, 0, 95);
	SetTranslate(0, 0);
	SetPosition(0, 0, 0);
	SetVisible(true);

	ZeroMemory(&vGamePos, sizeof(vGamePos));

	id = ItemID::MONEY;
	bHit = false;
}

void Item::Process()
{
	SetCollisionRect();

	if (bHit)
	{
		bVisible = false;
		bHit = false;
	}
}

void Item::SetCollisionRect()
{
	rtCollision.left = vGamePos.x - 10;
	rtCollision.right = rtCollision.left + 100;
	rtCollision.top = vGamePos.y - 10;
	rtCollision.bottom = rtCollision.top + 100;
}