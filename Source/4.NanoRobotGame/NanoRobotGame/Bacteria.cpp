#include "stdafx.h"

Bacteria::Bacteria()
{
}

Bacteria::Bacteria(LPDIRECT3DTEXTURE9 texture)
{
	Create();
	SetTexture(texture);
}

Bacteria::~Bacteria()
{
}

void Bacteria::Create()
{
	nFrameWidth = 270;
	nFrameHeight = 70;
	nFrameSpeed = 10;
	fMoveSpeed = 1.0f;
	lastFrame = 0;
	AniCount = 0;
	AniCurCount = 0;
	AniDieCount = 0;
	AniCurDieCount = 0;
	fHp = 10.0f;
	RandNum = GATIMER()->GetRand(3);
	bHit = false;
	bDie = false;
	bVisible = false;

	RECT rt;
	rt.left = 0;
	rt.right = nFrameWidth;
	rt.top = 0;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	motion = MotionState::UP;

	for (int i = 0; i < BACTERIA_MOVE; i++)
	{
		AniRect[AniCount].top = 0;
		AniRect[AniCount].left = i * nFrameWidth;
		AniRect[AniCount].right = AniRect[AniCount].left + nFrameWidth;
		AniRect[AniCount].bottom = nFrameHeight;
		AniCount++;
	}
	for (int i = 0; i < BACTERIA_DIE; i++)
	{
		DieRect[AniDieCount].top = nFrameHeight;
		DieRect[AniDieCount].left = (i)* nFrameWidth;
		DieRect[AniDieCount].right = DieRect[AniDieCount].left + nFrameWidth;
		DieRect[AniDieCount].bottom = DieRect[AniDieCount].top + nFrameHeight;
		AniDieCount++;
	}
}

void Bacteria::Animation()
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
		fHp = 10.0f;
		motion = MotionState::DIE;
	}

	if (vPosition.x < 0 - nFrameWidth && bVisible)
	{
		OBJMANAGER()->SetPlayerHP(1);
		bVisible = false;
	}
}

void Bacteria::AniMove()
{
	int nTimerFrame = GATIMER()->GetAbsoluteFrame();

	if (AniCurCount < BACTERIA_MOVE)
	{
		if (lastFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed)
		{
			SetRect(AniRect[AniCurCount++]);
			lastFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
	}
	if (AniCurCount >= BACTERIA_MOVE)
	{
		AniCurCount = 0;
	}
}

void Bacteria::AniDie()
{
	int nTimerFrame = GATIMER()->GetAbsoluteFrame();

	if (AniCurDieCount < BACTERIA_DIE)
	{
		if (lastFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed)
		{
			SetRect(DieRect[AniCurDieCount++]);
			lastFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
	}
	if (AniCurDieCount >= BACTERIA_DIE)
	{
		AniCurDieCount = 0;
		bDie = false;
		bVisible = false;
	}
}