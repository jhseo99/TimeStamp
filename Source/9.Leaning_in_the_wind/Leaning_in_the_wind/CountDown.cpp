#include "DXUT.h"
#include "GaBase.h"

CountDown::CountDown()
{
	Init();
}

CountDown::CountDown(LPDIRECT3DDEVICE9 pd3dDevice)
{
	CreateTexture(pd3dDevice, L"texture\\count.png");
	Init();
}

CountDown::~CountDown()
{
}

void CountDown::Init()
{
	fStartTime = 0.0f;
	SetRect(0, 175, 0, 250);
	SetTranslate(0, 0);
	SetPosition(312.5, 175, 0);
	SetVisible(true);
}

void CountDown::Process()
{
	if (GATIMER()->GetTimer() - fStartTime >= 1.0f)
	{
		rtRect.left = 175;
		rtRect.right = rtRect.left + 175;
	}
	if (GATIMER()->GetTimer() - fStartTime >= 2.0f)
	{
		rtRect.left = 2 * 175;
		rtRect.right = rtRect.left + 175;
	}
	if (GATIMER()->GetTimer() - fStartTime >= 3.0f)
	{
		rtRect.left = 3 * 175;
		rtRect.right = rtRect.left + 175;
	}
	if (GATIMER()->GetTimer() - fStartTime >= 3.5f)
	{
		SetRect(0, 175, 0, 250);
		fStartTime = 0.0f;
		SetVisible(false);
	}
}