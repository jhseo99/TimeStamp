#include "stdafx.h"

Cancer::Cancer()
{
}

Cancer::Cancer(LPDIRECT3DTEXTURE9 texture)
{
	Create();
	SetTexture(texture);
}

Cancer::~Cancer()
{
}

void Cancer::Create()
{
	nFrameWidth = 285;
	nFrameHeight = 280;
	nFrameSpeed = 10;
	AniCurCount = 0;
	fMoveSpeed = 0.2f;
	AniCount = 0;
	AniDieCount = 0;
	AniCurDieCount = 0;
	lastFrame = 0;
	fHp = 150.0f;
	this->bHit = false;
	bDie = false;
	bClear = false;
	bVisible = false;

	RECT rt;
	rt.left = 0;
	rt.right = nFrameWidth;
	rt.top = 0;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	motion = MotionState::UP;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			AniRect[AniCount].top = i * nFrameHeight;
			AniRect[AniCount].left = (j)* nFrameWidth;
			AniRect[AniCount].right = AniRect[j].left + nFrameWidth;
			AniRect[AniCount].bottom = AniRect[AniCount].top + nFrameHeight;
			AniCount++;
		}
	}

	for (int i = 0; i < CANCER_DIE; i++)
	{
		DieRect[AniDieCount].top = 2 * nFrameHeight;
		DieRect[AniDieCount].left = (i)* nFrameWidth;
		DieRect[AniDieCount].right = DieRect[AniDieCount].left + nFrameWidth;
		DieRect[AniDieCount].bottom = DieRect[AniDieCount].top + nFrameHeight;
		AniDieCount++;
	}
}

void Cancer::Animation()
{
	switch (motion)
	{
	case Enemy::MotionState::UP:
	case Enemy::MotionState::DOWN:
	case Enemy::MotionState::LEFT:
	case Enemy::MotionState::RIGHT:
		AniMove();
		break;
	case Enemy::MotionState::DIE:
		AniDie();
		break;
	default:
		break;
	}

	if (bHit && !bDie)
	{
		fHp--;
		bHit = false;
	}
	if (fHp <= 0)
	{
		bDie = true;
		fHp = 150;
		OBJMANAGER()->SetHumanHP(10);
		motion = MotionState::DIE;
	}
}

void Cancer::AniMove()
{
	int nTimerFrame = GATIMER()->GetAbsoluteFrame();

	if (AniCurCount < CANCER_MOVE)
	{
		if (lastFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed)
		{
			SetRect(AniRect[AniCurCount++]);
			lastFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
	}
	if (AniCurCount >= CANCER_MOVE)
	{
		AniCurCount = 0;
	}
}

void Cancer::AniDie()
{
	int nTimerFrame = GATIMER()->GetAbsoluteFrame();

	if (AniCurDieCount < CANCER_DIE)
	{
		if (lastFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed)
		{
			SetRect(DieRect[AniCurDieCount++]);
			lastFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
	}
	if (AniCurDieCount >= CANCER_DIE)
	{
		AniCurDieCount = 0;
		bDie = false;
		bVisible = false;
		bClear = true;
	}
}