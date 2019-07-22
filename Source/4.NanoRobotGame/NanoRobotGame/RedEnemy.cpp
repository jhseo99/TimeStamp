#include "stdafx.h"

RedEnemy::RedEnemy()
{
}

RedEnemy::RedEnemy(LPDIRECT3DTEXTURE9 texture)
{
	Create();
	SetTexture(texture);
}

RedEnemy::~RedEnemy()
{
}

void RedEnemy::Create()
{
	nFrameWidth = 140;
	nFrameHeight = 130;
	nFrameSpeed = 10;
	AniCurCount = 0;
	fMoveSpeed = 0.4f;
	AniCount = 0;
	AniCurDieCount = 0;
	AniDieCount = 0;
	lastFrame = 0;
	fHp = 5.0f;
	this->bHit = false;
	bDie = false;
	bVisible = false;

	RECT rt;
	rt.left = 0;
	rt.right = nFrameWidth;
	rt.top = 0;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	motion = MotionState::UP;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			AniRect[AniCount].top = i * nFrameHeight;
			AniRect[AniCount].left = (j)* nFrameWidth;
			AniRect[AniCount].right = AniRect[j].left + nFrameWidth;
			AniRect[AniCount].bottom = AniRect[AniCount].top + nFrameHeight;
			AniCount++;
		}
	}

	for (int i = 0; i < RED_DIE; i++)
	{
		DieRect[AniDieCount].top = 3 * nFrameHeight;
		DieRect[AniDieCount].left = (i)* nFrameWidth;
		DieRect[AniDieCount].right = DieRect[AniDieCount].left + nFrameWidth;
		DieRect[AniDieCount].bottom = DieRect[AniDieCount].top + nFrameHeight;
		AniDieCount++;
	}
}

void RedEnemy::Animation()
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
		fHp = 5;
		OBJMANAGER()->SetHumanHP(10);
		motion = MotionState::DIE;
	}
}

void RedEnemy::AniMove()
{
	int nTimerFrame = GATIMER()->GetAbsoluteFrame();
	
	if (AniCurCount < RED_MOVE)
	{
		if (lastFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed)
		{
			SetRect(AniRect[AniCurCount++]);
			lastFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
	}
	if (AniCurCount >= RED_MOVE)
	{
		AniCurCount = 0;
	}
}

void RedEnemy::AniDie()
{
	int nTimerFrame = GATIMER()->GetAbsoluteFrame();

	if (AniCurDieCount < RED_DIE)
	{
		if (lastFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed)
		{
			SetRect(DieRect[AniCurDieCount++]);
			lastFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
	}
	if (AniCurDieCount >= RED_DIE)
	{
		AniCurDieCount = 0;
		bDie = false;
		bVisible = false;
	}
}