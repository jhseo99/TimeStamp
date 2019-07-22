#include "DXUT.h"
#include "Boss.h"
#include "GaTimer.h"
#include "ObjectManager.h"

Boss::Boss()
{
}


Boss::~Boss()
{
}

void Boss::Respawn(float hp)
{
	vPosition.x = 1024.0f;
	vPosition.y = 200.0f;
	vPosition.z = 0.0f;

	moveState = MoveState::LEFT;
	fMoveRespawn = 0.0f;
	fMoveTime = 0.0f;

	fSpeed = 5.0f;

	bRespawn = true;
	bRandMove = false;

	bHitAni = false;
	fHitTime = 0.0f;
	bDie = false;

	bVisible = true;
	fHp = hp;

	pHpBar->SetVisible(true);
	for (int i = 0; i < MAX_BOSS_HP; i++)
	{
		pHp[i]->SetVisible(true);
	}
}

void Boss::Move()
{
	if (!bRandMove)
	{
		vPosition.x -= 2.0f;
		if (vPosition.x <= 600)
		{
			bRandMove = true;
		}
	}
	if (bRandMove)
	{
		if (GATIMER()->GetTimer() - fMoveRespawn > 1.0f)
		{
			int randNum = rand() % 4;
			switch (randNum)
			{
			case 0:
				moveState = MoveState::LEFT;
				break;
			case 1:
				moveState = MoveState::RIGHT;
				break;
			case 2:
				moveState = MoveState::UP;
				break;
			case 3:
				moveState = MoveState::DOWN;
				break;
			default:
				break;
			}

			fMoveRespawn = GATIMER()->GetTimer();
		}
		if (GATIMER()->GetTimer() - fMoveTime > 2.0f)
		{
			switch (moveState)
			{
			case MoveState::LEFT:
				vPosition.x -= fSpeed;
				if (vPosition.x < 500)
				{
					vPosition.x = 500;
				}
				break;
			case MoveState::RIGHT:
				vPosition.x += fSpeed;
				if (vPosition.x > 700)
				{
					vPosition.x = 700;
				}
				break;
			case MoveState::UP:
				vPosition.y -= fSpeed;
				if (vPosition.y < 0)
				{
					vPosition.y = 0;
				}
				break;
			case MoveState::DOWN:
				vPosition.y += fSpeed;
				if (vPosition.y > 200)
				{
					vPosition.y = 200;
				}
				break;
			default:
				break;
			}
			if (GATIMER()->GetTimer() - fMoveTime > 5.0f)
			{
				fMoveTime = GATIMER()->GetTimer();
			}
		}
	}
}