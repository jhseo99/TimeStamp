#pragma once
class RenderObject
{
public:
	RenderObject();
	~RenderObject();

protected:
	LPD3DXSPRITE pSprite;
	LPDIRECT3DTEXTURE9 pTexture;
	RECT rtRect;
	D3DXVECTOR3 vPosition;
	D3DCOLOR d3dColor;

	D3DXVECTOR2 vCenter;
	D3DXVECTOR2 vScale;
	D3DXVECTOR2 vTranslate;
	D3DXMATRIX matProj;

	int width;
	int height;

	float fSpriteAngle;

	bool bVisible;

public:
	virtual void InitRender();
	virtual void CreateTexture(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename);
	virtual void Render();

public:
	virtual LPD3DXSPRITE GetSprite() { return pSprite; }
	virtual void SetSprite(LPD3DXSPRITE sprite_) { pSprite = sprite_; }

	virtual LPDIRECT3DTEXTURE9 GetTexture() { return pTexture; }
	virtual void SetTexture(LPDIRECT3DTEXTURE9 texture_) { pTexture = texture_; }

	virtual RECT* GetRect() { return &rtRect; }
	virtual void SetRect(RECT rect_) { rtRect = rect_; }
	virtual void SetRect(int left, int right, int top, int bottom) { rtRect.left = left; rtRect.right = right; rtRect.top = top; rtRect.bottom = bottom; }

	virtual D3DXVECTOR3* GetPosition() { return &vPosition; }
	virtual void SetPosition(D3DXVECTOR3 position_) { vPosition = position_; }
	virtual void SetPosition(float x, float y, float z) { vPosition.x = x; vPosition.y = y; vPosition.z = z; }

	virtual D3DCOLOR GetColor() { return d3dColor; }
	virtual void SetColor(D3DCOLOR color_) { d3dColor = color_; }
	virtual void SetColor(float r, float g, float b, float a) { d3dColor = D3DCOLOR_COLORVALUE(r, g, b, a); }

	virtual D3DXVECTOR2* GetCenter() { return &vCenter; }
	virtual void SetCenter(D3DXVECTOR2 center_) { vCenter = center_; }
	virtual void SetCenter(float x, float y) { vCenter.x = x; vCenter.y = y; }

	virtual D3DXVECTOR2* GetScale() { return &vScale; }
	virtual void SetScale(D3DXVECTOR2 scale_) { vScale = scale_; }
	virtual void SetScale(float x, float y) { vScale.x = x; vScale.y = y; }

	virtual D3DXVECTOR2* GetTranslate() { return &vTranslate; }
	virtual void SetTranslate(D3DXVECTOR2 translate_) { vTranslate = translate_; }
	virtual void SetTranslate(float x, float y) { vTranslate.x = x; vTranslate.y = y; }

	virtual D3DXMATRIX* GetProj() { return &matProj; }
	virtual void SetProj(D3DXMATRIX proj_) { matProj = proj_; }

	virtual float GetSpriteAngle() { return fSpriteAngle; }
	virtual void SetSpriteAngle(float angle_) { fSpriteAngle = angle_; }

	virtual bool GetVisible() { return bVisible; }
	virtual void SetVisible(bool visible_) { bVisible = visible_; }
};

