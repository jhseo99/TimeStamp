#include "stdafx.h"

GameObject::GameObject()
{
}

GameObject::GameObject(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	Create(width, height);
	SetTexture(texture);
}

GameObject::~GameObject()
{
}

void GameObject::Create(int width, int height)
{
	nFrameWidth = width;
	nFrameHeight = height;
	bVisible = true;

	RECT rt;
	rt.left = 0;
	rt.right = width;
	rt.top = 0;
	rt.bottom = height;

	SetRect(rt);
}

void GameObject::MoveX(float speed)
{
	vPostion.x += speed;
}

void GameObject::MoveY(float speed)
{
	vPostion.y += speed;
}