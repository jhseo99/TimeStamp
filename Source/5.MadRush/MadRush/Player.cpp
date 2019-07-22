#include "stdafx.h"

Player::Player(void)
{
}

Player::Player(LPDIRECT3DTEXTURE9 texture, int x, int y)
{
	Create();
	SetTexture(texture);
	SetPosition(x, y, 0);
}

Player::~Player(void)
{
}

void Player::Create()
{
	nFrameWidth = 50;
	nFrameHeight = 100;
	bVisible = true;

	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = nFrameWidth;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	fSpeed = 5.0f;
	nCurAbsoluteFrame = 0;
	nCurrentShot = 0;

	fHp = 5;

	bHit = false;

	gunstate = GunState::ONE;

	CreateMissile();
}

void Player::Move()
{
	switch (move)
	{
	case Player::LEFT:
		vPosition.x -= fSpeed;
		if (vPosition.x <= 0)
		{
			vPosition.x = 0;
		}
		break;
	case Player::RIGHT:
		vPosition.x += fSpeed;
		if (vPosition.x + nFrameWidth >= 1024)
		{
			vPosition.x = 1024 - nFrameWidth;
		}
		break;
	case Player::UP:
		vPosition.y -= fSpeed;
		if (vPosition.y <= 0)
		{
			vPosition.y = 0;
		}
		break;
	case Player::DOWN:
		vPosition.y += fSpeed;
		if (vPosition.y + nFrameHeight >= 768)
		{
			vPosition.y = 768 - nFrameHeight;
		}
		break;
	}
}

void Player::Shoot(DWORD absoluteFrame)
{
	Hit();
	CreateMissile();

	if (absoluteFrame - nCurAbsoluteFrame > 5)
	{
		switch (gunstate)
		{
		case GunState::ONE:
			vecMissile[nCurrentShot]->SetShoot(true);
			vecMissile[nCurrentShot]->SetVisible(true);
			vecMissile[nCurrentShot]->SetFirePos((vPosition.x + (nFrameWidth / 2) - 5), vPosition.y);
			nCurrentShot++;
			break;
		case GunState::TWO:
			vecMissile[nCurrentShot]->SetShoot(true);
			vecMissile[nCurrentShot]->SetVisible(true);
			vecMissile[nCurrentShot]->SetFirePos((vPosition.x + (nFrameWidth / 2) - 5) - 20, vPosition.y);

			vecMissile[nCurrentShot + 1]->SetShoot(true);
			vecMissile[nCurrentShot + 1]->SetVisible(true);
			vecMissile[nCurrentShot + 1]->SetFirePos((vPosition.x + (nFrameWidth / 2) - 5) + 20, vPosition.y);
			nCurrentShot += 2;
			break;
		case GunState::THREE:
			vecMissile[nCurrentShot]->SetShoot(true);
			vecMissile[nCurrentShot]->SetVisible(true);
			vecMissile[nCurrentShot]->SetFirePos((vPosition.x + (nFrameWidth / 2) - 5), vPosition.y);

			vecMissile[nCurrentShot + 1]->SetShoot(true);
			vecMissile[nCurrentShot + 1]->SetVisible(true);
			vecMissile[nCurrentShot + 1]->SetFirePos((vPosition.x + (nFrameWidth / 2) - 5) + 5, vPosition.y);

			vecMissile[nCurrentShot + 2]->SetShoot(true);
			vecMissile[nCurrentShot + 2]->SetVisible(true);
			vecMissile[nCurrentShot + 2]->SetFirePos((vPosition.x + (nFrameWidth / 2) - 5) - 5, vPosition.y);
			nCurrentShot += 3;
			break;
		}
		if (nCurrentShot > nMissileCount - 1)
		{
			nCurrentShot = 0;
		}

		nCurAbsoluteFrame = absoluteFrame;
	}
}

void Player::CreateMissile()
{
	nMissileCount = 150;

	vecMissile.reserve(nMissileCount);

	Missile* pTemp = NULL;

	for (int i = 0; i < nMissileCount; i++)
	{
		pTemp = new Missile(OBJMANAGER()->GetTexture(GaBase::TextureID::MISSILE), 10, 20);
		vecMissile.push_back(pTemp);

		switch (gunstate)
		{
		case GunState::ONE:
		case GunState::TWO:
			vecMissile[i]->SetGradiant(0);
			break;
		case GunState::THREE:
			if ((i + 1) % 3 == 0)
			{
				vecMissile[i]->SetGradiant(1.5);
			}
			else if ((i + 2) % 3 == 0)
			{
				vecMissile[i]->SetGradiant(-1.5);
			}
			break;
		}
	}
}

void Player::Hit()
{
}

void Player::Reset()
{
	Create();
}

void Player::Process()
{
}