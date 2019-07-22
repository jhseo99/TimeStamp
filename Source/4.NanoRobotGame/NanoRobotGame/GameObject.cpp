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
	bVisible = true;
	
	nFrameWidth = width;
	nFrameHeight = height;

	RECT rt;
	rt.left = 0;
	rt.right = nFrameWidth;
	rt.top = 0;
	rt.bottom = nFrameHeight;

	SetRect(rt);
}

void GameObject::MoveX(float speed)
{
	this->vPosition.x += speed;
}

void GameObject::MoveY(float speed)
{
	this->vPosition.y += speed;
}