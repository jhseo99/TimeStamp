#pragma once
#include "Object.h"

#define ANI_EFFECT 20

class Effect
	:public Object
{
public:
	Effect();
	~Effect();

private:
	RECT rtEffect[ANI_EFFECT];
	int AniEffectCount;
	int AniCurEffect;

	float lastEffect;

	bool bFinish;

public:
	void SetAniEffect(int width, int height, int widthNum, int heightNum);
	void AniEffect(int MaxEffect);

public:
	bool GetFinish() { return bFinish; }
	void SetFinish(bool finish) { bFinish = finish; }
};

