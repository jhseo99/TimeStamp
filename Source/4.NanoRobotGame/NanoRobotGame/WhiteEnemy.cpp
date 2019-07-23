#include "stdafx.h"

WhiteEnemy::WhiteEnemy()
{
}

WhiteEnemy::WhiteEnemy(LPDIRECT3DTEXTURE9 texture)
{
	Create();
	SetTexture(texture);
}

WhiteEnemy::~WhiteEnemy()
{
}

void WhiteEnemy::Create()
{
	nFrameWidth = 100;
	nFrameHeight = 100;
	nFrameSpeed = 10;
	fMoveSpeed = 2.5f;
	lastFrame = 0;
	AniCount = 0;
	AniCurCount = 0;
	AniCurDieCount = 0;
	AniDieCount = 0;
	fHp = 3;
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

	for (int i = 0; i < WHITE_MOVE; i++)
	{
		AniRect[AniCount].top = 0;
		AniRect[AniCount].left = i * nFrameWidth;
		AniRect[AniCount].right = AniRect[AniCount].left + nFrameWidth;
		AniRect[AniCount].bottom = nFrameHeight;
		AniCount++;
	}

	for (int i = 0; i < WHITE_DIE; i++)
	{
		DieRect[AniDieCount].top = nFrameHeight;
		DieRect[AniDieCount].left = (i)* nFrameWidth;
		DieRect[AniDieCount].right = DieRect[AniDieCount].left + nFrameWidth;
		DieRect[AniDieCount].bottom = DieRect[AniDieCount].top + nFrameHeight;
		AniDieCount++;
	}
}

void WhiteEnemy::Animation()
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
		fHp = 3.0f;
		motion = MotionState::DIE;
	}
}

void WhiteEnemy::AniMove()
{
	int nTimerFrame = GATIMER()->GetAbsoluteFrame();

	if (AniCurCount < WHITE_MOVE)
	{
		if (lastFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed)
		{
			SetRect(AniRect[AniCurCount++]);
			lastFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
	}
	if (AniCurCount >= WHITE_MOVE)
	{
		AniCurCount = 0;
	}
}

void WhiteEnemy::AniDie()
{
	int nTimerFrame = GATIMER()->GetAbsoluteFrame();

	if (AniCurDieCount < WHITE_DIE)
	{
		if (lastFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed)
		{
			SetRect(DieRect[AniCurDieCount++]);
			lastFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
	}
	if (AniCurDieCount >= WHITE_DIE)
	{
		AniCurDieCount = 0;
		bDie = false;
		bVisible = false;
	}
}