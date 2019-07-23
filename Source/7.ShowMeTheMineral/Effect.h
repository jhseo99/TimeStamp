#pragma once
#include "Object.h"

#define MAX_ANI 20

class Effect
	:public Object
{
public:
	Effect();
	Effect(LPDIRECT3DTEXTURE9 texture, int width, int height, int widthNum, int heightNum);
	~Effect();

private:
	RECT rtAni[MAX_ANI];
	float fAniTime;
	int nAniCount;
	int nCurrentAni;

	bool bFinish;

public:
	void Create(int width, int height, int widthNum, int heightNum);
	void Animation(float fTime, int MaxNum, bool bLoop);

	bool GetFinish() { return bFinish; }
	void SetFinish(bool finish) { bFinish = finish; }
};

