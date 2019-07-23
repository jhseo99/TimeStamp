#include "DXUT.h"
#include "Effect.h"


Effect::Effect()
{
}


Effect::~Effect()
{
}

void Effect::SetAniEffect(int width, int height, int widthNum, int heightNum)
{
	bVisible = false;
	RECT rt;
	rt.left = 0;
	rt.right = width;
	rt.top = 0;
	rt.bottom = height;
	SetRect(rt);

	AniEffectCount = 0;
	AniCurEffect = 0;

	lastEffect = 0;

	for (int i = 0; i < heightNum; i++)
	{
		for (int j = 0; j < widthNum; j++)
		{
			rtEffect[AniEffectCount].left = j * width;
			rtEffect[AniEffectCount].right = rtEffect[AniEffectCount].left + width;
			rtEffect[AniEffectCount].top = i * height;
			rtEffect[AniEffectCount].bottom = rtEffect[AniEffectCount].top + height;
			AniEffectCount++;
		}
	}
}

void Effect::AniEffect(int MaxEffect)
{
	if (DXUTGetTime() - lastEffect > 0.1f)
	{
		SetRect(rtEffect[AniCurEffect++]);
		lastEffect = DXUTGetTime();
	}
	if (AniCurEffect >= MaxEffect)
	{
		bVisible = false;
		bFinish = true;
		AniCurEffect = 0;
	}
}