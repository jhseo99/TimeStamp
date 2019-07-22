#pragma once
#include "Object.h"

class Ending
{
public:
	Ending();
	~Ending();

private:
	Object* pEnding;
	int nCharCount;
	bool bKeyDown;

public:
	void Create();
	void Update();
	void Render();
	void KeyProc();
};

