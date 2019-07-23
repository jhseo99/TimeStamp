#pragma once

class Object
{
public:
	Object(void);
	~Object(void);

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
	float fSpeed;
	float fHp;
	bool bHit;

public:
	virtual void Create();
	virtual void Process();
	virtual void CollisonCheck(Object* object);
	virtual void ItemCollisonCheck(Object* object);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void Destroy();

public:
	// Get & Set
	virtual LPDIRECT3DTEXTURE9 GetTexture() { return pTexture; }
	virtual void SetTexture(LPDIRECT3DTEXTURE9 texture) { pTexture = texture; }

	virtual RECT* GetRect() { return &rtSize; }
	virtual void SetRect(RECT _rt) { rtSize = _rt; }

	virtual RECT* GetCollsonRect() { return &rtCollison; }
	virtual void SetCollison(int left, int right, int top, int bottom);

	virtual D3DXVECTOR3* GetPosition() { return &vPosition; }
	virtual void SetPosition(D3DXVECTOR3 vPos) { vPosition = vPos; }
	virtual void SetPosition(int x, int y, int z) { vPosition.x = x; vPosition.y = y; vPosition.z = z; }

	virtual D3DXVECTOR3* GetCenter() { return &vCenter; }

	virtual D3DCOLOR GetColor() { return d3dColor; }
	virtual void SetColorAlpha(float alpha) { d3dColor = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, alpha); }

	virtual void SetSpeed(float _speed) { fSpeed = _speed; }

	virtual float GetHp() { return fHp; }
	virtual void SetHp(float _hp) { fHp = _hp; }

	virtual bool GetHit() { return bHit; }
	virtual void SetHit(bool _hit) { bHit = _hit; }

	virtual bool GetVisible() { return bVisible; }
	virtual void SetVisible(bool visible) { bVisible = visible; }

	virtual int GetFameWidth() { return nFrameWidth; }
	virtual int GetFameHeight() { return nFrameHeight; }
};