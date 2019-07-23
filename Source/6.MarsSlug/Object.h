#pragma once

class Object
{
public:
	Object();
	~Object();

protected:
	LPD3DXSPRITE pSprite;
	D3DXMATRIX mWorld;
	LPDIRECT3DTEXTURE9 pTexture;
	RECT rtSize;
	RECT rtCollision;
	D3DXVECTOR3 vCenter;
	D3DXVECTOR3 vPosition;
	D3DCOLOR d3dColor;
	bool bVisible;
	bool bHit;
	bool bHitAni;
	bool bDie;
	float fHp;

public:
	virtual void Create(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename);
	virtual void Render();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void UpdateCollision(int left, int right, int top, int bottom);
	virtual void Destroy();

public:
	virtual D3DXMATRIX* GetWorld() { return &mWorld; }
	virtual void SetWorld(D3DXMATRIX world) { mWorld = world; }

	virtual LPDIRECT3DTEXTURE9 GetTexture() { return pTexture; }

	virtual RECT* GetRect() { return &rtSize; }
	virtual void SetRect(RECT size) { rtSize = size; }

	virtual RECT* GetCollision() { return &rtCollision; }
	virtual void SetCollision(RECT collision) { rtCollision = collision; }

	virtual D3DXVECTOR3* GetCenter() { return &vCenter; }
	virtual void SetCenter(D3DXVECTOR3 center) { vCenter = center; }

	virtual D3DXVECTOR3* GetPosition() { return &vPosition; }
	virtual void SetPosition(D3DXVECTOR3 position) { vPosition = position; }

	virtual D3DCOLOR GetColor() { return d3dColor; }
	virtual void SetColor(D3DCOLOR color) { d3dColor = color; }

	virtual bool GetVisible() { return bVisible; }
	virtual void SetVisible(bool visible) { bVisible = visible; }

	virtual bool GetHit() { return bHit; }
	virtual void SetHit(bool hit) { bHit = hit; }
};

