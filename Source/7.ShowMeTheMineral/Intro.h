#pragma once
#include "Object.h"

class Intro
{
public:
	Intro();
	~Intro();

private:
	Object* pIntro;

public:
	void Create();
	void Update();
	void Render();
};

