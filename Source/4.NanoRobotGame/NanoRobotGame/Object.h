#pragma once
class Object
{
public:
	Object();
	~Object();

protected:
	LPDIRECT3DTEXTURE9 pTexture;
	RECT rtSize;
	RECT rtCollison;
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vCenter;
	D3DCOLOR d3dColor;
	bool bVisible;
	int nFrameWidth;
	int nFrameHeight;
	UINT nFrameSpeed;
	DWORD nCurAbsoluteFrame;
	float fHp;
	bool bHit;

public:
	virtual void Process();
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void CollisonCheck(Object* object);
	virtual void Destroy();

public:
	virtual LPDIRECT3DTEXTURE9 GetTexture() { return pTexture; }
	virtual void SetTexture(LPDIRECT3DTEXTURE9 texture) { pTexture = texture; }

	virtual RECT* GetRect() { return &rtSize; }
	virtual void SetRect(RECT rt) { rtSize = rt; }

	virtual RECT* GetCollisonRect() { return &rtCollison; }
	virtual void SetCollisonRect(int left, int right, int top, int bottom);

	virtual D3DXVECTOR3* GetPosition() { return &vPosition; }
	virtual void SetPosition(D3DXVECTOR3 vPos) { vPosition = vPos; }
	virtual void SetPosition(int x, int y, int z) { vPosition.x = x; vPosition.y = y; vPosition.z = z; }

	virtual D3DXVECTOR3* GetCenter() { return &vCenter; }

	virtual D3DCOLOR GetColor() { return d3dColor; }
	virtual void SetColorAlpha(float _alpha) { d3dColor = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, _alpha); }

	virtual bool GetVisible() { return bVisible; }
	virtual void SetVisible(bool visible) { bVisible = visible; }

	virtual bool GetHit() { return bHit; }
	virtual void SetHit(bool hit) { bHit = hit; }
};