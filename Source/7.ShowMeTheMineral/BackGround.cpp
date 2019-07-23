#include "DXUT.h"
#include "BackGround.h"
#include "ObjectManager.h"

BackGround::BackGround()
{
}

BackGround::BackGround(LPDIRECT3DTEXTURE9 texture, float x, float y)
{
	SetTexture(texture);
	Create(x, y);
}

BackGround::~BackGround()
{
}

void BackGround::Create(float x, float y)
{
	SetRect(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	SetPosition(x, y, 0);
	bVisible = true;

	D3DXCreateSprite(OBJMANAGER()->GetDevice(), &pSprite);
}

void BackGround::Move(float fSpeed, float fLimit)
{
	vPosition.x -= fSpeed;

	if (vPosition.x <= -fLimit)
	{
		vPosition.x = fLimit;
	}
}