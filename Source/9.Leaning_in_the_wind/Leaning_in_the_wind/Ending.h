#pragma once
class Ending
{
public:
	Ending();
	~Ending();

private:
	RenderObject* pEnding;
	RenderObject* pStar1;
	RenderObject* pStar2;
	RenderObject* pMessage;

	float fAlpha;
	float fAlpha2;

public:
	void Create(LPDIRECT3DDEVICE9 pd3dDevice);
	void Update();
	void Render();
};

