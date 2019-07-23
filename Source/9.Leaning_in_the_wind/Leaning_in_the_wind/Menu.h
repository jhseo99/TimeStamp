#pragma once
class Menu
{
public:
	Menu();
	~Menu();

private:
	RenderObject* pMenu;

public:
	void Create(LPDIRECT3DDEVICE9 pd3dDevice);
	void Update();
	void Render();
};

