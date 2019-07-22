#pragma once
class RenderObject
{
public:
	RenderObject();
	~RenderObject();

public:
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;
	RECT m_rtRect;
	D3DXVECTOR3 m_vCenter;
	D3DXVECTOR3 m_vPosition;
	D3DCOLOR m_d3dColor;
	D3DXMATRIX m_matWorld;

	bool m_bVisible;

public:
	virtual void Init();
	virtual void CreateTexture(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename);
	virtual void Render();

public:
	virtual void SetRect(RECT rt) { m_rtRect = rt; };
	virtual void SetRect(int left, int right, int top, int bottom) { m_rtRect.left = left; m_rtRect.right = right; m_rtRect.top = top; m_rtRect.bottom = bottom; }

	virtual void SetPosition(D3DXVECTOR3 pos) { m_vPosition = pos; }
	virtual void SetPosition(float x, float y, float z) { m_vPosition.x = x; m_vPosition.y = y; m_vPosition.z = z; }

	virtual void SetColor(D3DCOLOR color) { m_d3dColor = color; };
	virtual void SetColor(float r, float g, float b, float a) { m_d3dColor = D3DCOLOR_COLORVALUE(r, g, b, a); }
};