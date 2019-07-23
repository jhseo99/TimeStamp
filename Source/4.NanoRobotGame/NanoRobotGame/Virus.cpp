#include "stdafx.h"


Virus::Virus()
{
}

Virus::Virus(LPDIRECT3DTEXTURE9 texture)
{
	Create();
	SetTexture(texture);
}

Virus::~Virus()
{
}

void Virus::Create()
{
	nFrameWidth = 120;
	nFrameHeight = 120;
	nFrameSpeed = 10;
	fMoveSpeed = 2.0f;
	lastFrame = 0;
	AniCurCount = 0;
	AniCount = 0;
	AniDieCount = 0;
	AniCurDieCount = 0;
	fHp = 1.0f;
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

	for (int i = 0; i < VIRUS_DIE; i++)
	{
		DieRect[AniDieCount].top = 3 * nFrameHeight;
		DieRect[AniDieCount].left = (i)* nFrameWidth;
		DieRect[AniDieCount].right = DieRect[AniDieCount].left + nFrameWidth;
		DieRect[AniDieCount].bottom = DieRect[AniDieCount].top + nFrameHeight;
		AniDieCount++;
	}
}

void Virus::Animation()
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
		bDie = true;
		bHit = false;
		fHp = 1.0f;
		motion = MotionState::DIE;
	}

	if (vPosition.x < 0 - nFrameWidth && bVisible)
	{
		OBJMANAGER()->SetPlayerHP(2);
		bVisible = false;
	}
}

void Virus::AniMove()
{
	int nTimerFrame = GATIMER()->GetAbsoluteFrame();

	if (AniCurCount < VIRUS_MOVE)
	{
		if (lastFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed)
		{
			SetRect(AniRect[AniCurCount++]);
			lastFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
	}
	if (AniCurCount >= VIRUS_MOVE)
	{
		AniCurCount = 0;
	}
}

void Virus::AniDie()
{
	int nTimerFrame = GATIMER()->GetAbsoluteFrame();

	if (AniCurDieCount < VIRUS_DIE)
	{
		if (lastFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed)
		{
			SetRect(DieRect[AniCurDieCount++]);
			lastFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
	}
	if (AniCurDieCount >= VIRUS_DIE)
	{
		AniCurDieCount = 0;
		bDie = false;
		bVisible = false;
	}
}