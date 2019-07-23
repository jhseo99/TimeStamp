#include "DXUT.h"
#include "GaBase.h"


Horse::Horse()
{
}

Horse::~Horse()
{
}

void Horse::Init()
{
	pSheild.SetRect(0, 200, 0, 200);
	pSheild.SetTranslate(0, 0);
	pSheild.SetPosition(300, 200, 0);
	pSheild.SetVisible(false);

	bVisible = true;
	SetRect(0, 200, 0, 200);
	SetTranslate(0, 0);

	SpriteHeight = 0;

	fSpeed = 5.0f;
	fAccel = 0.01f;
	fStamina = 0.0f;
	fMaxStamina = 0.0f;
	fMaxSpeed = 0.0f;

	vGamePos.x = 0.0f;
	vGamePos.y = 0.0f;

	nCollisionLeft = 0;
	nCollisionRight = 0;
	nCollisionTop = 0;
	nCollisionBottom = 0;
	
	fCollisionCircleX = 0.0f;
	fCollisionCircleY = 0.0f;
	fCollisionCircleR = 0.0f;

	fCollisionCircleCenterX = 0.0f;
	fCollisionCircleCenterY = 0.0f;

	bSpeedUp = false;
	fMoney = 0.0f;

	bSheild = false;

	fBoostTime = 0.0f;
	bBoost = false;

	bFire = false;
	fFireTime = 0.0f;

	fDistance = 0.0f;
	
	bHit = false;
	fHitTime = 0.0f;

	bGoal = false;

	bShelidItem = false;
	bBoostItem = false;
	bFireItem = false;

	ZeroMemory(&vDirectVec, sizeof(vDirectVec));
	ZeroMemory(&vCrossVec, sizeof(vCrossVec));

	state = State::IDLE;

	fRunFrameTime = 0.0f;
	nCurrentRunFrame = 1;
}

void Horse::SetHorseStat(LPDIRECT3DDEVICE9 pd3dDevice)
{
	switch (id)
	{
	case Horse::JEJU:
		fMaxSpeed = 7.9f;
		fAccel = 0.018f;
		fMaxStamina = 95.0f;
		fStamina = fMaxStamina;
		CreateTexture(pd3dDevice, L"texture\\horse.png");
		break;
	case Horse::BUSAN:
		fMaxSpeed = 8.0f;
		fAccel = 0.016f;
		fMaxStamina = 95.0f;
		fStamina = fMaxStamina;
		CreateTexture(pd3dDevice, L"texture\\horse2.png");
		break;
	case Horse::SEOUL:
		fMaxSpeed = 8.1f;
		fAccel = 0.018f;
		fMaxStamina = 85.0f;
		fStamina = fMaxStamina;
		CreateTexture(pd3dDevice, L"texture\\horse3.png");
		break;
	case Horse::KWANGJU:
		fMaxSpeed = 8.0f;
		fAccel = 0.018f;
		fMaxStamina = 90.0f;
		fStamina = fMaxStamina;
		CreateTexture(pd3dDevice, L"texture\\horse1.png");
		break;
	default:
		break;
	}
}


void Horse::SetDirectVec(float x1, float y1, float x2, float y2)
{
	vDirectVec.x = x2 - x1;
	vDirectVec.y = y2 - y1;
	vDirectVec.z = 0.0f;

	D3DXVec3Normalize(&vDirectVec, &vDirectVec);
}

void Horse::Process()
{
	vCrossVec.x = vDirectVec.y;
	vCrossVec.y = -vDirectVec.x;
	vCrossVec.z = 0.0f;

	D3DXVec3Normalize(&vCrossVec, &vCrossVec);

	if (fStamina < fMaxStamina)
	{
		fStamina += 0.05f;
	}
	if (fSpeed >= fMaxSpeed - 1 && (!bSpeedUp && !bBoost))
	{
		fSpeed -= 0.01f;
		if (fSpeed <= fMaxSpeed - 1)
		{
			fSpeed = fMaxSpeed - 1;
		}
	}

	Advance();
	SetCollisionRect();
	SetCollisionCircle();
	Fire();
	Boost();
	HitSystem();

	pSheild.SetPosition(vPosition.x, vPosition.y, 0);
	pSheild.SetVisible(bSheild);

	pFire.SetPosition(vPosition.x - 25, vPosition.y - 30, 0);
	pFire.SetCollisionRect(vGamePos.x - 25, 250, vGamePos.y - 30, 260);
	pFire.SetVisible(bFire);
	pFire.Animation();
}

void Horse::Advance()
{
	if (state != State::IDLE)
	{
		vGamePos.x += vDirectVec.x * fSpeed;
		vGamePos.y += vDirectVec.y * fSpeed;
	}
}


void Horse::SetCollisionRect()
{
	switch (direction)
	{
	case Direction::LEFT:
		nCollisionLeft = 47;
		nCollisionRight = 102;
		nCollisionTop = 56;
		nCollisionBottom = 56;
		break;
	case Direction::RIGHT:
		nCollisionLeft = 48;
		nCollisionRight = 102;
		nCollisionTop = 60;
		nCollisionBottom = 56;
		break;
	case Direction::UP:
		nCollisionLeft = 84;
		nCollisionRight = 35;
		nCollisionTop = 34;
		nCollisionBottom = 152;
		break;
	case Direction::DOWN:
		nCollisionLeft = 83;
		nCollisionRight = 35;
		nCollisionTop = 44;
		nCollisionBottom = 152;
		break;
	case Direction::LUP:
		nCollisionLeft = 71;
		nCollisionRight = 63;
		nCollisionTop = 64;
		nCollisionBottom = 72;
		break;
	case Direction::RUP:
		nCollisionLeft = 67;
		nCollisionRight = 62;
		nCollisionTop = 61;
		nCollisionBottom = 72;
		break;
	case Direction::LDOWN:
		nCollisionLeft = 57;
		nCollisionRight = 93;
		nCollisionTop = 62;
		nCollisionBottom = 64;
		break;
	case Direction::RDOWN:	
		nCollisionLeft = 48;
		nCollisionRight = 93;
		nCollisionTop = 66;
		nCollisionBottom = 64;
		break;
	default:
		break;
	}

	rtCollision.left = vGamePos.x + nCollisionLeft;
	rtCollision.right = rtCollision.left + nCollisionRight;
	rtCollision.top = vGamePos.y + nCollisionTop + 100;
	rtCollision.bottom = rtCollision.top + nCollisionBottom;
}

void Horse::SetCollisionCircle()
{
	switch (direction)
	{
	case Direction::LEFT:
		fCollisionCircleR = 28.5;
		fCollisionCircleX = 100;
		fCollisionCircleY = 113;
		break;
	case Direction::RIGHT:
		fCollisionCircleR = 28.5;
		fCollisionCircleX = 100;
		fCollisionCircleY = 113;
		break;
	case Direction::UP:
		fCollisionCircleR = 26.5;
		fCollisionCircleX = 101;
		fCollisionCircleY = 80;
		break;
	case Direction::DOWN:
		fCollisionCircleR = 26.5;
		fCollisionCircleX = 101;
		fCollisionCircleY = 131;
		break;
	case Direction::LUP:
		fCollisionCircleR = 20;
		fCollisionCircleX = 84;
		fCollisionCircleY = 106;
		break;
	case Direction::RUP:
		fCollisionCircleR = 20;
		fCollisionCircleX = 113;
		fCollisionCircleY = 106;
		break;
	case Direction::LDOWN:
		fCollisionCircleR = 20;
		fCollisionCircleX = 103;
		fCollisionCircleY = 106;
		break;
	case Direction::RDOWN:
		fCollisionCircleR = 35;
		fCollisionCircleX = 103;
		fCollisionCircleY = 106;
		break;
	default:
		break;
	}

	fCollisionCircleCenterX = vGamePos.x + fCollisionCircleX;
	fCollisionCircleCenterY = vGamePos.y + fCollisionCircleY + fCollisionCircleR;
}

void Horse::SetTextureRect()
{
	switch (direction)
	{
	case Direction::LEFT:
		SpriteHeight = 2;
		break;
	case Direction::RIGHT:
		SpriteHeight = 6;
		break;
	case Direction::UP:
		SpriteHeight = 0;
		break;
	case Direction::DOWN:
		SpriteHeight = 4;
		break;
	case Direction::LUP:
		SpriteHeight = 1;
		break;
	case Direction::RUP:
		SpriteHeight = 7;
		break;
	case Direction::LDOWN:
		SpriteHeight = 3;
		break;
	case Direction::RDOWN:
		SpriteHeight = 5;
		break;
	default:
		break;
	}

	rtRect.top = 200 * SpriteHeight;
	rtRect.bottom = rtRect.top + 200;
}

void Horse::Animation()
{
	switch (state)
	{
	case Horse::IDLE:
		rtRect.left = 0;
		rtRect.right = 200;
		break;
	case Horse::RUN:
		AniRun();
		break;
	case Horse::JUMP:
		break;
	default:
		break;
	}
}

void Horse::AniRun()
{
	if (GATIMER()->GetTimer() - fRunFrameTime > 0.1f)
	{
		rtRect.left = nCurrentRunFrame * 200;
		rtRect.right = rtRect.left + 200;

		nCurrentRunFrame++;
		fRunFrameTime = GATIMER()->GetTimer();
	}
	if (nCurrentRunFrame >= ANI_RUN)
	{
		nCurrentRunFrame = 1;
	}
}


void Horse::SpeedUp()
{
	if (fSpeed >= fMaxSpeed)
	{
		fSpeed = fMaxSpeed;
	}
	if (fStamina < 0)
	{
		fStamina = 0;
		fSpeed = 5.0f;
	}
	else
	{
		fStamina -= 0.2f;
		fSpeed += fAccel;
	}
}

void Horse::SpeedDown()
{
	fSpeed -= 0.05f;
	if (fSpeed <= 5)
	{
		fSpeed = 5.0f;
	}
}

void Horse::MoveLeft()
{
	vGamePos.x += vCrossVec.x * fSpeed / 1.5;
	vGamePos.y += vCrossVec.y * fSpeed / 1.5;
}

void Horse::MoveRight()
{
	vGamePos.x -= vCrossVec.x * fSpeed / 1.5;
	vGamePos.y -= vCrossVec.y * fSpeed / 1.5;
}

void Horse::SetItem(Item* pItem)
{
	switch (pItem->GetID())
	{
	case Item::ItemID::MONEY:
		fMoney += (float)((rand() % 90) + 10);
		break;
	case Item::ItemID::SHEILD:
		bShelidItem = true;
		bBoostItem = false;
		bFireItem = false;
		break;
	case Item::ItemID::BOOST:
		bShelidItem = false;
		bBoostItem = true;
		bFireItem = false;
		break;
	case Item::ItemID::WIND:
		bShelidItem = false;
		bBoostItem = false;
		bFireItem = true;
		break;
	default:
		break;
	}
}

void Horse::Fire()
{
	if (bFire)
	{
		if (GATIMER()->GetTimer() - fFireTime > 3.0f)
		{
			bFire = false;
		}
	}
}

void Horse::Boost()
{
	if (bBoost)
	{
		if (GATIMER()->GetTimer() - fBoostTime > 3.0f)
		{
			bBoost = false;
		}
		else
		{
			SpeedUp();
			fStamina += 0.2f;
		}
	}
}

void Horse::HitSystem()
{
	if (bHit)
	{
		if (GATIMER()->GetTimer() - fHitTime > 2.0f)
		{
			state = State::RUN;
			bHit = false;
			if (bSheild)
			{
				bSheild = false;
			}
		}
		else
		{
			if (!bSheild)
			{
				state = State::IDLE;
			}
		}
	}
}

void Horse::Clear()
{
	pSheild.SetRect(0, 200, 0, 200);
	pSheild.SetTranslate(0, 0);
	pSheild.SetPosition(300, 200, 0);
	pSheild.SetVisible(false);

	fSpeed = 5.0f;
	fStamina = fMaxStamina;

	bVisible = true;
	SetRect(0, 200, 0, 200);
	SetTranslate(0, 0);

	SpriteHeight = 0;

	nCollisionLeft = 0;
	nCollisionRight = 0;
	nCollisionTop = 0;
	nCollisionBottom = 0;

	fCollisionCircleX = 0.0f;
	fCollisionCircleY = 0.0f;
	fCollisionCircleR = 0.0f;

	fCollisionCircleCenterX = 0.0f;
	fCollisionCircleCenterY = 0.0f;

	bSpeedUp = false;

	bSheild = false;

	fBoostTime = 0.0f;
	bBoost = false;

	bFire = false;
	fFireTime = 0.0f;

	fDistance = 0.0f;

	bHit = false;
	fHitTime = 0.0f;

	bGoal = false;

	bShelidItem = false;
	bBoostItem = false;
	bFireItem = false;

	state = State::IDLE;

	fRunFrameTime = 0.0f;
	nCurrentRunFrame = 1;
}