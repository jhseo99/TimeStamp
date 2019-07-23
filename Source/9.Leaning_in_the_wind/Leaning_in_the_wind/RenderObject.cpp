#include "DXUT.h"
#include "GaBase.h"


RenderObject::RenderObject()
{
	InitRender();
}


RenderObject::~RenderObject()
{
}

void RenderObject::InitRender()
{
	pSprite = NULL;
	pTexture = NULL;
	ZeroMemory(&rtRect, sizeof(&rtRect));
	ZeroMemory(&vPosition, sizeof(&vPosition));
	d3dColor = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);
	
	ZeroMemory(&vCenter, sizeof(vCenter));
	ZeroMemory(&vTranslate, sizeof(vTranslate));
	vScale.x = 1.0f;
	vScale.y = 1.0f;

	width = 0;
	height = 0;
	
	fSpriteAngle = 0.0f;

	bVisible = false;
}

void RenderObject::CreateTexture(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename)
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
								NULL,
								NULL,
								NULL,
								&pTexture);
}

void RenderObject::Render()
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	width = rtRect.right - rtRect.left;
	height = rtRect.bottom - rtRect.top;

	vCenter.x = (float)(width * vScale.x / 2) + vPosition.x;
	vCenter.y = (float)(height * vScale.y / 2) + vPosition.y;

	D3DXMatrixTransformation2D(&matProj, NULL, 0.0, &vScale, &vCenter, fSpriteAngle, &vTranslate);

	pSprite->SetTransform(&matProj);

	if (bVisible && pSprite != NULL && pTexture != NULL)
	{
		pSprite->Draw(pTexture, &rtRect, NULL, &vPosition, d3dColor);
	}

	pSprite->End();
}