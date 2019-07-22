#include "DXUT.h"
#include "GaBase.h"


HorseAI::HorseAI()
{
	InitAI();
}

HorseAI::HorseAI(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename)
{
	CreateTexture(pd3dDevice, filename);

	InitAI();

	pSheild.CreateTexture(pd3dDevice, L"texture\\Sheild.png");
	pFire.Fire::Fire(pd3dDevice);
}

HorseAI::~HorseAI()
{
}

void HorseAI::InitAI()
{
	Init();
	fSpeed = 5.0f;
	fPathUpdateTime = 0.0f;
	nWay = 0;
	bSpeed = false;
}

void HorseAI::Process()
{
	SpeedUpdate();
	SetWay();	
	switch (nWay)
	{
	case 0:
		MoveLeft();
		break;
	case 1:
		MoveRight();
		break;
	default:
		break;
	}

	pSheild.SetTranslate(GetTranslate()->x, GetTranslate()->y);

	pFire.SetTranslate(GetTranslate()->x, GetTranslate()->y);

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
	pSheild.SetVisible(bSheild);

	Horse::Process();

	vPosition.x = vGamePos.x + 300;
	vPosition.y = vGamePos.y + 200;
	vPosition.z = 0.0f;
}

void HorseAI::SetWay()
{
	if (GATIMER()->GetTimer() - fPathUpdateTime >= 0.5f)
	{
		nWay = (int)(rand() % 4);

		fPathUpdateTime = GATIMER()->GetTimer();
	}
}

void HorseAI::SpeedUpdate()
{
	bSpeedUp = false;
	if (fSpeed < fMaxSpeed && fStamina >= fMaxStamina / 1.5)
	{
		bSpeed = true;
	}
	if (bSpeed)
	{
		SpeedUp();
		bSpeedUp = true;
		if (fStamina <= 1.0)
		{
			bSpeed = false;
		}
	}
}