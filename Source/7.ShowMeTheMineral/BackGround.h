#pragma once
#include "Object.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

class BackGround
	:public Object
{
public:
	BackGround();
	BackGround(LPDIRECT3DTEXTURE9 texture, float x, float y);
	~BackGround();

public:
	void Create(float x, float y);
	void Move(float fSpeed, float fLimit);
};

