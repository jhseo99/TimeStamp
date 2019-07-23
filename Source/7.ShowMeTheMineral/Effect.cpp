#include "DXUT.h"
#include "Effect.h"
#include "GaTimer.h"

Effect::Effect()
{
}

Effect::Effect(LPDIRECT3DTEXTURE9 texture, int width, int height, int widthNum, int heightNum)
{
	SetTexture(texture);
	Create(width, height, widthNum, heightNum);
}

Effect::~Effect()
{
}

void Effect::Create(int width, int height, int widthNum, int heightNum)
{
	SetRect(0, width, 0, height);

	fAniTime = 0.0f;
	nAniCount = 0;
	nCurrentAni = 0;
	bFinish = false;

	bVisible = false;

	for (int i = 0; i < heightNum; i++)
	{
		for (int j = 0; j < widthNum; j++)
		{
			rtAni[nAniCount].left = j * width;
			rtAni[nAniCount].right = rtAni[nAniCount].left + width;
			rtAni[nAniCount].top = i * height;
			rtAni[nAniCount].bottom = rtAni[nAniCount].top + height;
			nAniCount++;
		}
	}
}

void Effect::Animation(float fTime, int MaxNum, bool bLoop)
{
	if (GATIMER()->GetTimer() - fAniTime > fTime && bVisible)
	{
		SetRect(rtAni[nCurrentAni++]);

		fAniTime = GATIMER()->GetTimer();
	}
	if (bLoop)
	{
		if (nCurrentAni >= MaxNum)
		{
			nCurrentAni = 0;
		}
	}
	else if (!bLoop)
	{
		if (nCurrentAni >= MaxNum)
		{
			nCurrentAni = 0;
			bVisible = false;
			bFinish = true;
		}
	}
}