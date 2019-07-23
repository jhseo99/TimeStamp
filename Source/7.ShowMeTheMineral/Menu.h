#pragma once
#include "Object.h"

class Menu
{
public:
	Menu();
	~Menu();

private:
	Object* pMenu;
	bool bClick;

public:
	void Create();
	void Update();
	void Render();
	void MouseProc(UINT uMsg);
};

