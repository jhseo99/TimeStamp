#pragma once
class Intro
{
public:
	Intro();
	~Intro();

private:
	RenderObject* pBeach;
	RenderObject* pCloud1;
	RenderObject* pCloud2;
	RenderObject* pTitle;

public:
	void Create(LPDIRECT3DDEVICE9 pd3dDevice);
	void Update();
	void Render();
};

