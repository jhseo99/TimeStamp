#pragma once

class Object
{
public:
	Object();
	~Object();

protected:
	LPDIRECT3DTEXTURE9 pTexture;
	RECT rtSize;
	RECT rtCollision;
	D3DXVECTOR3 vPostion;
	D3DXVECTOR2 vDirection;
	D3DXVECTOR3 vCenter;
	D3DCOLOR d3dColor;
	bool bVisible;
	int nFrameWidth;
	int nFrameHeight;
	UINT nFrameSpeed;
	float fSpeed;
	bool bHit;

public:
	virtual void Create();
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void Destroy();
	virtual void CollisionCheck(Object* object);
	virtual void HitProcess();

public:
	virtual LPDIRECT3DTEXTURE9 GetTexture() { return pTexture;}
	virtual void SetTexture(LPDIRECT3DTEXTURE9 texture) { pTexture = texture; }

	virtual RECT* GetRect() { return &rtSize; }
	virtual void SetRect(RECT size) { rtSize = size; }

	virtual RECT* GetCollisionRect() { return &rtCollision; }
	virtual void SetCollisionRect(int left, int right, int top, int bottom);

	virtual D3DXVECTOR3* GetPosition() { return &vPostion; }
	virtual void SetPosition(D3DXVECTOR3 vPos) { vPostion = vPos; }
	virtual void SetPosition(float x, float y, float z) { vPostion.x = x; vPostion.y = y; vPostion.z = z; }

	virtual D3DXVECTOR2* GetDirection() { return &vDirection; }
	virtual void SetDirection(D3DXVECTOR2 vec) { vDirection = vec; }

	virtual D3DXVECTOR3* GetCenter() { return &vCenter; }

	virtual D3DCOLOR GetColor() { return d3dColor; }
	virtual void SetColorAlpha(float alpha) { D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, alpha); }

	virtual bool GetVisible() { return bVisible; }
	virtual void SetVisible(bool visible) { bVisible = visible; }

	virtual float GetSpeed() { return fSpeed; }
	virtual void SetSpeed(float speed) { fSpeed = speed; }

	virtual bool GetHit() { return bHit; }
	virtual void SetHit(bool hit) { bHit = hit; }
};