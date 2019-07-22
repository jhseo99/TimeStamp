#include "DXUT.h"
#include "Object.h"


Object::Object()
{
	pSprite = NULL;
	pTexture = NULL;
	ZeroMemory(&rtRect, sizeof(rtRect));
	ZeroMemory(&vCenter, sizeof(vCenter));
	ZeroMemory(&vPosition, sizeof(vPosition));
	ZeroMemory(&vCenterPos, sizeof(vCenterPos));
	d3dColor = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);
	bVisible = false;
	fHp = 0.0f;
	bHit = false;
}

Object::Object(LPDIRECT3DTEXTURE9 texture, int width, int height, float x, float y)
{
	pSprite = NULL;
	pTexture = NULL;
	ZeroMemory(&rtRect, sizeof(rtRect));
	ZeroMemory(&vCenter, sizeof(vCenter));
	ZeroMemory(&vPosition, sizeof(vPosition));
	ZeroMemory(&vCenterPos, sizeof(vCenterPos));
	d3dColor = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);
	bVisible = false;
	fHp = 0.0f;
	bHit = false;

	SetTexture(texture);
	Create(width, height, x, y);
}

Object::~Object()
{
	Destroy();
}

void Object::SetCollision(int left, int right, int top, int bottom)
{
	rtCollision.left = vPosition.x + left;
	rtCollision.right = rtCollision.left + right;
	rtCollision.top = vPosition.y + top;
	rtCollision.bottom = rtCollision.top + bottom;
}

void Object::Create(int width, int height, float x, float y)
{
	SetRect(0, width, 0, height);
	SetPosition(x, y, 0);
	bVisible = true;
}

void Object::Render()
{
	this->pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (bVisible)
	{
		this->pSprite->Draw(GetTexture(), GetRect(), GetCenter(), GetPosition(), GetColor());
	}

	this->pSprite->End();
}

void Object::Render(LPD3DXSPRITE pSprite)
{	
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (bVisible)
	{
		pSprite->Draw(GetTexture(), GetRect(), GetCenter(), GetPosition(), GetColor());
	}

	pSprite->End();
}

void Object::Destroy()
{
	delete this;
}