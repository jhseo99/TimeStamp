#include "DXUT.h"
#include "Object.h"


Object::Object()
{
	pSprite = NULL;
	pTexture = NULL;
	ZeroMemory(&mWorld, sizeof(mWorld));
	ZeroMemory(&rtSize, sizeof(rtSize));
	ZeroMemory(&vCenter, sizeof(vCenter));
	ZeroMemory(&vPosition, sizeof(vPosition));
	d3dColor = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);
	bVisible = false;
	bHit = false;
	bDie = false;
	bHitAni = false;
}


Object::~Object()
{
	Destroy();
}

void Object::Create(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename)
{
	D3DXCreateSprite(pd3dDevice, &pSprite);

	D3DXCreateTextureFromFileEx(pd3dDevice, 
		filename, 
		D3DX_DEFAULT, D3DX_DEFAULT, 
		1, 
		0,
		D3DFMT_A8R8G8B8, 
		D3DPOOL_MANAGED, 
		D3DX_FILTER_NONE, 
		D3DX_FILTER_NONE, 
		0, 
		NULL, 
		NULL, 
		&pTexture);
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


void Object::UpdateCollision(int left, int right, int top, int bottom)
{
	rtCollision.left = vPosition.x + left;
	rtCollision.right = rtCollision.left + right;
	rtCollision.top = vPosition.y + top;
	rtCollision.bottom = rtCollision.top + bottom;
}

void Object::Destroy()
{
	if (pSprite != NULL)
	{
		pSprite = NULL;
	}
}