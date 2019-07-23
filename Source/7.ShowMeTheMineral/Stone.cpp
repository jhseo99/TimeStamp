#include "DXUT.h"
#include "Stone.h"
#include "ObjectManager.h"

Stone::Stone()
{
	D3DXCreateSprite(OBJMANAGER()->GetDevice(), &pSprite);
	bVisible = false;
	bHit = false;
}

Stone::Stone(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	Create(width, height);
}

Stone::~Stone()
{
}

void Stone::Create(int width, int height)
{
	SetRect(0, width, 0, height);

	stoneType = StoneType::WAVE;

	bVisible = false;
	bHit = false;
	D3DXCreateSprite(OBJMANAGER()->GetDevice(), &pSprite);
}

void Stone::Respawn()
{
	vPosition.x = 1024.0f;
	vPosition.y = 768 - rtRect.bottom;
	vPosition.z = 0;

	bVisible = true;
	bHit = false;
}

void Stone::Update()
{
	if (bVisible)
	{
		vPosition.x -= 8.0f;
		
		switch (stoneType)
		{
		case StoneType::WAVE:
			SetCollision(&rtStoneCollsion[0], 127, 218, 14, 76);
			SetCollision(&rtStoneCollsion[1], 15, 452, 101, 91);
			SetCollision(&rtStoneCollsion[2], 0, 0, 1000, 0);
			break;
		case StoneType::FREEWAVE:
			SetCollision(&rtStoneCollsion[0], 40, 192, 82, 84);
			SetCollision(&rtStoneCollsion[1], 257, 52, 69, 139);
			SetCollision(&rtStoneCollsion[2], 310, 123, 15, 195);
			break;
		case StoneType::HORN:
			SetCollision(&rtStoneCollsion[0], 119, 25, 9, 99);
			SetCollision(&rtStoneCollsion[1], 85, 86, 108, 166);
			SetCollision(&rtStoneCollsion[2], 0, 0, 1000, 0);
			break;
		case StoneType::HOLE:
			SetCollision(&rtStoneCollsion[0], 0, 0, 1000, 0);
			SetCollision(&rtStoneCollsion[1], 0, 0, 1000, 0);
			SetCollision(&rtStoneCollsion[2], 0, 0, 1000, 0);
			break;
		default:
			break;
		}
	}
}

void Stone::SetCollision(RECT* rect, int left, int right, int top, int bottom)
{
	rect->left = vPosition.x + left;
	rect->right = rect->left + right;
	rect->top = vPosition.y + top;
	rect->bottom = rect->top + bottom;
}