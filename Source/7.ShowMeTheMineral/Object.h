#pragma once

class Object
{
public:
	Object();
	Object(LPDIRECT3DTEXTURE9 texture, int width, int height, float x, float y);
	~Object();

protected:
	LPD3DXSPRITE pSprite;
	LPDIRECT3DTEXTURE9 pTexture;
	RECT rtRect;
	RECT rtCollision;
	D3DXVECTOR3 vCenter;
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vCenterPos;
	D3DCOLOR d3dColor;
	bool bVisible;
	float fHp;
	bool bHit;

public:
	virtual void Create(int width, int height, float x, float y);
	virtual void Render();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

public:
	virtual LPD3DXSPRITE GetSprite() { return pSprite; }

	virtual LPDIRECT3DTEXTURE9 GetTexture() { return pTexture; }
	virtual void SetTexture(LPDIRECT3DTEXTURE9 texture) { pTexture = texture; }

	virtual RECT* GetRect() { return &rtRect; }
	virtual void SetRect(RECT rect) { rtRect = rect; }
	virtual void SetRect(int left, int right, int top, int bottom) { rtRect.left = left; rtRect.right = right; rtRect.top = top; rtRect.bottom = bottom; }

	virtual RECT* GetCollision() { return &rtCollision; }
	virtual void SetCollision(RECT rect) { rtCollision = rect; }
	virtual void SetCollision(int left, int right, int top, int bottom);

	virtual D3DXVECTOR3* GetCenter() { return &vCenter; }
	virtual void SetCenter(D3DXVECTOR3 center) { vCenter = center; }
	virtual void SetCenter(float x, float y, float z) { vCenter.x = x; vCenter.y = y; vCenter.z = z; }

	virtual D3DXVECTOR3* GetPosition() { return &vPosition; }
	virtual void SetPosition(D3DXVECTOR3 position) { vPosition = position; }
	virtual void SetPosition(float x, float y, float z) { vPosition.x = x; vPosition.y = y; vPosition.z = z; }

	virtual D3DXVECTOR3* GetCenterPos() { return &vCenterPos; }
	virtual void SetCenterPos(D3DXVECTOR3 position) { vCenterPos= position; }
	virtual void SetCenterPos(float x, float y, float z) { vCenterPos.x = x; vCenterPos.y = y; vCenterPos.z = z; }

	virtual D3DCOLOR GetColor() { return d3dColor; }
	virtual void SetColor(D3DCOLOR color) { d3dColor = color; }
	virtual void SetColor(float r, float g, float b, float a) { d3dColor = D3DCOLOR_COLORVALUE(r, g, b, a); }

	virtual bool GetVisible() { return bVisible; }
	virtual void SetVisible(bool visible) { bVisible = visible; }

	virtual float GetHp() { return fHp; }
	virtual void SetHp(float hp) { fHp = hp; }

	virtual bool GetHit() { return bHit; }
	virtual void SetHit(bool hit) { bHit = hit; }
};

