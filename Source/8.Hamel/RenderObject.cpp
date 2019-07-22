#include "DXUT.h"
#include "GaBase.h"


RenderObject::RenderObject()
{
	Init();
}


RenderObject::~RenderObject()
{
}

void RenderObject::Init()
{
	m_pSprite = NULL;
	m_pTexture = NULL;
	ZeroMemory(&m_rtRect, sizeof(m_rtRect));
	ZeroMemory(&m_vCenter, sizeof(m_vCenter));
	ZeroMemory(&m_vPosition, sizeof(m_vPosition));

	m_d3dColor = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&m_matWorld, 0, 0, 0);
}

void RenderObject::CreateTexture(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename)
{
	D3DXCreateSprite(pd3dDevice, &m_pSprite);

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
								&m_pTexture);
}

void RenderObject::Render()
{
	if (m_pSprite != NULL && m_pTexture != NULL)
	{
		m_pSprite->SetTransform(&m_matWorld);

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		if (m_bVisible)
		{
			m_pSprite->Draw(m_pTexture, &m_rtRect, &m_vCenter, &m_vPosition, m_d3dColor);
		}

		m_pSprite->End();
	}
}