#include "DXUT.h"
#include "GaBase.h"


PlayerHorse::PlayerHorse()
{
	Init();
}

PlayerHorse::PlayerHorse(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename)
{
	CreateTexture(pd3dDevice, filename);

	Init();

	pSheild.CreateTexture(pd3dDevice, L"texture\\Sheild.png");
	pFire.Fire::Fire(pd3dDevice);
}

PlayerHorse::~PlayerHorse()
{
}

void PlayerHorse::Process()
{
	KeyProc();

	Horse::Process();
}

void PlayerHorse::KeyProc()
{
	bSpeedUp = false;
	switch (direction)
	{
	case Direction::LEFT:
	case Direction::RIGHT:
	case Direction::UP:
	case Direction::LUP:
	case Direction::RUP:
		if (GetAsyncKeyState(VK_UP))
		{
			SpeedUp();
			bSpeedUp = true;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			SpeedDown();
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			MoveLeft();
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			MoveRight();
		}
		break;
	case Direction::DOWN:
	case Direction::LDOWN:
	case Direction::RDOWN:
		if (GetAsyncKeyState(VK_UP))
		{
			SpeedUp();
			bSpeedUp = true;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			SpeedDown();
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			MoveRight();
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			MoveLeft();
		}
		break;
	default:
		break;
	}
	if (GetAsyncKeyState('X'))
	{
		if (bBoostItem)
		{
			bBoostItem = false;
			fBoostTime = GATIMER()->GetTimer();
			bBoost = true;
		}
		if (bFireItem)
		{
			bFireItem = false;
			bFire = true;
			fFireTime = GATIMER()->GetTimer();
		}
		if (bShelidItem)
		{
			bShelidItem = false;
			bSheild = true;
		}
	}
}