#include "DXUT.h"
#include "Player.h"
#include "ObjectManager.h"
#include "GaTimer.h"

Player::Player()
{
}

Player::Player(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

Player::~Player()
{
}

void Player::Create()
{
	SetRect(0, PLAYER_WIDTH, 0, PLAYER_HEIGHT);
	SetPosition(10, 350, 0);

	fHp = 5.0f;
	fSpeed = 5.0f;
	fDamage = 1.0f;
	fDefence = 50.0f;

	fBulletTime = 0.0f;
	nBulletCount = 0;
	nGunLevel = 1;
	fGunTime = 0.0f;

	bVisible = true;
	bHit = false;

	moveState = MoveState::LEFT;
	gunState = GunState::BASE;
	beforeGun = gunState;

	fAniMoveTime = 0.0f;
	nMoveCount = 0;
	nCurrentMove = 0;

	bBomb = false;
	nBombCount = 3;

	fDefenceTime = 0.0f;

	bHitAni = false;
	fHitTime = 0.0f;

	nAddonLevel = 0;

	bPhenix = false;

	pFireEffect = new Effect(OBJMANAGER()->GetTexture(GaBase::TextureID::PLAYER_FIRE), 60, 60, 6, 1);
	pBombEffect = new Effect(OBJMANAGER()->GetTexture(GaBase::TextureID::PLAYER_BOMB), 1024, 768, 8, 1);

	for (int i = 0; i < MAX_ADDON; i++)
	{
		pAddon[i] = new AddOnPlayer(OBJMANAGER()->GetTexture(GaBase::TextureID::ADD_ON));
	}

	D3DXMatrixTranslation(&matCamera, 0.0f, 0.0f, 0.0f);

	CreateBullet();
	SetAniRect();
}

void Player::Update()
{
	SetCollision(47, 55, 12, 25);
	SetCenterPos(vPosition.x + 70, vPosition.y + 12, 0);

	if (bVisible)
	{
		// GunSet
		if (gunState != GunState::MISSILE && 
			gunState != GunState::MISSILE_THREE && 
			gunState != GunState::MISSILE_AIM)
		{
			switch (nGunLevel)
			{
			case 1:
				gunState = GunState::BASE;
				break;
			case 2:
				gunState = GunState::DOUBLE;
				break;
			case 3:
				gunState = GunState::THREE;
				break;
			default:
				break;
			}
		}
		// Missile
		MissileSystem();
		// Ani
		AniMove();
		// Fire
		pFireEffect->SetPosition(vPosition.x + 90, vPosition.y + 5, 0);
		pFireEffect->Animation(0.02f, 6, false);
		if (pFireEffect->GetFinish())
		{
			pFireEffect->SetFinish(false);
		}
		// Bomb
		if (bBomb)
		{
			pBombEffect->SetVisible(true);
			pBombEffect->Animation(0.1f, 8, false);
			CameraMove();
		}
		if (pBombEffect->GetFinish())
		{
			pBombEffect->SetFinish(false);
			bBomb = false;
			D3DXMatrixTranslation(&matCamera, 0.0f, 0.0f, 0.0f);
		}
		// Defence
		DefenceUp();
		// HitSystem
		HitSystem();
		// AddOn
		AddOn();
	}

	// Bullet
	for (int i = 0; i < PLAYER_MAX_BULLET; i++)
	{
		pBullet[i]->SetCollision(0, 25, 0, 10);
		pMissile[i]->SetCollision(0, 50, 0, 25);
		pAimMissile[i]->SetCollision(0, 50, 0, 25);

		pBullet[i]->Shot();
		pMissile[i]->Shot();
		pAimMissile[i]->Shot();
	}

	// Damage
	switch (gunState)
	{
	case GunState::BASE:
		fDamage = 1.0f + nAddonLevel;
		break;
	case GunState::DOUBLE:
		fDamage = 1.0f + nAddonLevel;
		break;
	case GunState::THREE:
		fDamage = 1.0f + nAddonLevel;
		break;
	case GunState::MISSILE:
		fDamage = 2.0f + nAddonLevel;
		break;
	case GunState::MISSILE_THREE:
		fDamage = 2.0f + nAddonLevel;
		break;
	case GunState::MISSILE_AIM:
		fDamage = 15.0f + nAddonLevel;
		break;
	default:
		break;
	}
}

void Player::Move()
{
	switch (moveState)
	{
	case MoveState::LEFT:
		vPosition.x -= fSpeed;
		if (vPosition.x <= 0)
		{
			vPosition.x = 0;
		}
		break;
	case MoveState::RIGHT:
		vPosition.x += fSpeed;
		if (vPosition.x >= 1024 - PLAYER_WIDTH)
		{
			vPosition.x = 1024 - PLAYER_WIDTH;
		}
		break;
	case MoveState::UP:
		vPosition.y -= fSpeed;
		if (vPosition.y <= 0)
		{
			vPosition.y = 0;
		}
		break;
	case MoveState::DOWN:
		vPosition.y += fSpeed;
		if (vPosition.y >= 580)
		{
			vPosition.y = 580;
		}
		break;
	default:
		break;
	}
}

void Player::CreateBullet()
{
	for (int i = 0; i < PLAYER_MAX_BULLET; i++)
	{
		pBullet[i] = new Bullet(OBJMANAGER()->GetTexture(GaBase::TextureID::PLAYER_BULLET), 25, 10);
		pMissile[i] = new Bullet(OBJMANAGER()->GetTexture(GaBase::TextureID::PLAYER_MISSILE), 50, 25);
		pAimMissile[i] = new AimBullet(OBJMANAGER()->GetTexture(GaBase::TextureID::PLAYER_MISSILE_AIM), 50, 25);
	}
}

void Player::Shot()
{
	pFireEffect->SetVisible(true);

	switch (gunState)
	{
	case GunState::BASE:
		BaseShot(pBullet);
		fDamage = 1.0f + nAddonLevel;
		beforeGun = GunState::BASE;
		break;
	case GunState::DOUBLE:
		DoubleShot(pBullet);
		fDamage = 1.0f;
		beforeGun = GunState::DOUBLE;
		break;
	case GunState::THREE:
		ThreeShot(pBullet);
		fDamage = 1.0f + nAddonLevel;
		beforeGun = GunState::THREE;
		break;
	case GunState::MISSILE:
		BaseShot(pMissile);
		fDamage = 2.0f + nAddonLevel;
		break;
	case GunState::MISSILE_THREE:
		ThreeShot(pMissile);
		fDamage = 2.0f + nAddonLevel;
		break;
	case GunState::MISSILE_AIM:
		AimShot(pAimMissile);
		fDamage = 15.0f + nAddonLevel;
		break;
	default:
		break;
	}
}

void Player::BaseShot(Bullet* pBullet[])
{
	if (GATIMER()->GetTimer() - fBulletTime > 0.2f)
	{
		pBullet[nBulletCount]->SetVisible(true);
		pBullet[nBulletCount]->SetPosition(vPosition.x + 80, vPosition.y + 35, 0);
		pBullet[nBulletCount]->SetSpeed(15.0f);
		pBullet[nBulletCount]->SetAngle(0.0f);
		pBullet[nBulletCount]->SetShot(true);

		nBulletCount++;
		fBulletTime = GATIMER()->GetTimer();
	}
	if (nBulletCount >= PLAYER_MAX_BULLET)
	{
		nBulletCount = 0;
	}
}

void Player::DoubleShot(Bullet* pBullet[])
{
	if (GATIMER()->GetTimer() - fBulletTime > 0.15f)
	{
		pBullet[nBulletCount]->SetVisible(true);
		pBullet[nBulletCount]->SetPosition(vPosition.x + 80, vPosition.y + 25, 0);
		pBullet[nBulletCount]->SetSpeed(20.0f);
		pBullet[nBulletCount]->SetAngle(0.0f);
		pBullet[nBulletCount]->SetShot(true);

		pBullet[nBulletCount+1]->SetVisible(true);
		pBullet[nBulletCount+1]->SetPosition(vPosition.x + 80, vPosition.y + 45, 0);
		pBullet[nBulletCount+1]->SetSpeed(20.0f);
		pBullet[nBulletCount+1]->SetAngle(0.0f);
		pBullet[nBulletCount+1]->SetShot(true);

		nBulletCount += 2;
		fBulletTime = GATIMER()->GetTimer();
	}
	if (nBulletCount >= PLAYER_MAX_BULLET - 2)
	{
		nBulletCount = 0;
	}
}

void Player::ThreeShot(Bullet* pBullet[])
{
	if (GATIMER()->GetTimer() - fBulletTime > 0.15f)
	{
		pBullet[nBulletCount]->SetVisible(true);
		pBullet[nBulletCount]->SetPosition(vPosition.x + 80, vPosition.y + 35, 0);
		pBullet[nBulletCount]->SetSpeed(25.0f);
		pBullet[nBulletCount]->SetAngle(0.0f);
		pBullet[nBulletCount]->SetShot(true);

		pBullet[nBulletCount + 1]->SetVisible(true);
		pBullet[nBulletCount + 1]->SetPosition(vPosition.x + 80, vPosition.y + 35, 0);
		pBullet[nBulletCount + 1]->SetSpeed(25.0f);
		pBullet[nBulletCount + 1]->SetAngle(0.1f);
		pBullet[nBulletCount + 1]->SetShot(true);

		pBullet[nBulletCount + 2]->SetVisible(true);
		pBullet[nBulletCount + 2]->SetPosition(vPosition.x + 80, vPosition.y + 35, 0);
		pBullet[nBulletCount + 2]->SetSpeed(25.0f);
		pBullet[nBulletCount + 2]->SetAngle(-0.1f);
		pBullet[nBulletCount + 2]->SetShot(true);

		nBulletCount += 3;
		fBulletTime = GATIMER()->GetTimer();
	}
	if (nBulletCount >= PLAYER_MAX_BULLET - 3)
	{
		nBulletCount = 0;
	}
}

void Player::AimShot(AimBullet* pBullet[])
{
	if (GATIMER()->GetTimer() - fBulletTime > 0.5f)
	{
		pBullet[nBulletCount]->SetVisible(true);
		pBullet[nBulletCount]->SetPosition(vPosition.x + 80, vPosition.y + 35, 0);
		pBullet[nBulletCount]->SetSpeed(15.0f);
		pBullet[nBulletCount]->SetAngle(0.0f);
		pBullet[nBulletCount]->SetShot(true);
		pBullet[nBulletCount]->SetAim(false);

		nBulletCount++;
		fBulletTime = GATIMER()->GetTimer();
	}
	if (nBulletCount >= PLAYER_MAX_BULLET)
	{
		nBulletCount = 0;
	}
}

void Player::MissileSystem()
{
	if (GATIMER()->GetTimer() - fGunTime > 10.0f &&
		(gunState == GunState::MISSILE ||
		 gunState == GunState::MISSILE_THREE ||
		 gunState == GunState::MISSILE_AIM))
	{
		gunState = beforeGun;

		fGunTime = GATIMER()->GetTimer();
	}
}

void Player::SetAniRect()
{
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtMove[nMoveCount].left = i * PLAYER_WIDTH;
		rtMove[nMoveCount].right = rtMove[nMoveCount].left + PLAYER_WIDTH;
		rtMove[nMoveCount].top = 0;
		rtMove[nMoveCount].bottom = PLAYER_HEIGHT;
		nMoveCount++;
	}
}

void Player::AniMove()
{
	if (GATIMER()->GetTimer() - fAniMoveTime > 0.2f)
	{
		SetRect(rtMove[nCurrentMove++]);
		
		fAniMoveTime = GATIMER()->GetTimer();
	}
	if (nCurrentMove >= ANI_MOVE)
	{
		nCurrentMove = 0;
	}
}

void Player::Bomb()
{
	if (!bBomb && nBombCount > 0)
	{
		bBomb = true;
		nBombCount--;
	}
}

void Player::CameraMove()
{
	int randNum = rand() % 4;

	switch (randNum)
	{
	case 0:
		D3DXMatrixTranslation(&matCamera, -10.0f, 0.0f, 0.0f);
		break;
	case 1:
		D3DXMatrixTranslation(&matCamera, 10.0f, 0.0f, 0.0f);
		break;
	case 2:
		D3DXMatrixTranslation(&matCamera, 0.0f, -10.0f, 0.0f);
		break;
	case 3:
		D3DXMatrixTranslation(&matCamera, 0.0f, 10.0f, 0.0f);
		break;
	default:
		break;
	}
}

void Player::DefenceUp()
{
	if (GATIMER()->GetTimer() - fDefenceTime > 0.5f && fDefence < 100)
	{
		fDefence++;
		
		fDefenceTime = GATIMER()->GetTimer();
	}
}

void Player::HitSystem()
{
	if (bHit)
	{
		if (!bHitAni && !bPhenix)
		{
			fDefence -= 100.0f;
			if (fDefence < 0)
			{
				fHp--;
				fDefence = 0.0f;
				bHitAni = true;
				fHitTime = GATIMER()->GetTimer();
			}
		}
		bHit = false;
	}
	if (bHitAni)
	{
		CameraMove();
		if (GATIMER()->GetTimer() - fHitTime > 1.0f)
		{
			D3DXMatrixTranslation(&matCamera, 0.0f, 0.0f, 0.0f);
			bHitAni = false;

			fHitTime = GATIMER()->GetTimer();
		}
	}
}

void Player::AddOn()
{
	if (nAddonLevel == 1)
	{
		pAddon[0]->SetVisible(true);
		pAddon[0]->SetPosition(vPosition.x + 70, vPosition.y + 60, 0);
		pAddon[0]->Update();
	}
	if (nAddonLevel == 2)
	{
		pAddon[0]->SetVisible(true);
		pAddon[0]->SetPosition(vPosition.x + 70, vPosition.y + 60, 0);
		pAddon[0]->Update();

		pAddon[1]->SetVisible(true);
		pAddon[1]->SetPosition(vPosition.x + 50, vPosition.y + 80, 0);
		pAddon[1]->Update();
	}
}