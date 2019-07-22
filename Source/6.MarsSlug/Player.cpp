#include "DXUT.h"
#include "Player.h"

Player Player::singleton;

Player::Player()
{
	InitPlayer();
}


Player::~Player()
{
}

void Player::InitPlayer()
{
	bVisible = true;

	RECT rt;
	rt.left = 0;
	rt.right = PLAYER_WIDTH;
	rt.top = 0;
	rt.bottom = PLAYER_HEIGHT;
	SetRect(rt);

	D3DXVECTOR3 vPos;
	vPos.x = 50.0f;
	vPos.y = 300.0f;
	vPos.z = 0.0f;
	SetPosition(vPos);

	fSpeed = 7.5f;
	AniCount = 1;

	fLastBullet = 0;
	nCurBullet = 0;

	AniIdleCount = 0;
	AniCurIdle = 0;

	AniCurBack = 0;

	AniLittleTopCount = 0;
	AniCurLittleTop = 0;

	AniChangeLTCount = 0;
	AniCurChangeLT = 0;

	AniTopCount = 0;
	AniCurTop = 0;

	AniChangeTCount = 0;
	AniCurChangeT = 0;

	AniLittleBottomCount = 0;
	AniCurLittleBottom = 0;

	AniChangeLBCount = 0;
	AniCurChangeLB = 0;

	AniBottomCount = 0;
	AniCurBottom = 0;

	AniChangeBCount = 0;
	AniCurChangeB = 0;

	fHp = 10.0f;

	lastFrame = 0;

	gunDirection = GunDirection::IDLE;

	SetAniRect();
	CreateBullet();
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
		if (vPosition.x >= 1600 - PLAYER_HEIGHT)
		{
			vPosition.x = 1600 - PLAYER_HEIGHT;
		}
		break;
	case MoveState::UP:
		vPosition.y -= fSpeed;
		if (vPosition.y <= 150)
		{
			vPosition.y = 150;
		}
		break;
	case MoveState::DOWN:
		vPosition.y += fSpeed;
		if (vPosition.y >= 700)
		{
			vPosition.y = 700;
		}
		break;
	}
}

void Player::Shot()
{
	D3DXVECTOR3 vFirePos;

	if (DXUTGetTime() - fLastBullet > 0.2f)
	{
		switch (gunDirection)
		{
		case GunDirection::IDLE:
			vFirePos.x = vPosition.x + 140;
			vFirePos.y = vPosition.y + (PLAYER_HEIGHT / 2) - 15;
			vFirePos.z = 0;

			pBullet[nCurBullet]->SetShot(true);
			pBullet[nCurBullet]->SetVisible(true);
			pBullet[nCurBullet]->SetPosition(vFirePos);
			pBullet[nCurBullet]->SetGradiant(0);
			pBullet[nCurBullet]->SetSpeedX(20.0f);
			nCurBullet++;
			break;
		case GunDirection::BACK:
			break;
		case GunDirection::LITTLETOP:
			vFirePos.x = vPosition.x + 130;
			vFirePos.y = vPosition.y + (PLAYER_HEIGHT / 2) - 60.0f;
			vFirePos.z = 0;

			pBullet[nCurBullet]->SetShot(true);
			pBullet[nCurBullet]->SetVisible(true);
			pBullet[nCurBullet]->SetGradiant(1.5f);
			pBullet[nCurBullet]->SetPosition(vFirePos);
			pBullet[nCurBullet]->SetSpeedX(20.0f);
			nCurBullet++;
			break;
		case GunDirection::TOP:
			vFirePos.x = vPosition.x + 50;
			vFirePos.y = vPosition.y;
			vFirePos.z = 0;

			pBullet[nCurBullet]->SetShot(true);
			pBullet[nCurBullet]->SetVisible(true);
			pBullet[nCurBullet]->SetGradiant(2.5f);
			pBullet[nCurBullet]->SetPosition(vFirePos);
			pBullet[nCurBullet]->SetSpeedX(0.0f);
			nCurBullet++;
			break;
		case GunDirection::LITTLEBOTTOM:
			vFirePos.x = vPosition.x + 130;
			vFirePos.y = vPosition.y + (PLAYER_HEIGHT / 2) + 60.0f;
			vFirePos.z = 0;

			pBullet[nCurBullet]->SetShot(true);
			pBullet[nCurBullet]->SetVisible(true);
			pBullet[nCurBullet]->SetGradiant(-1.5f);
			pBullet[nCurBullet]->SetPosition(vFirePos);
			pBullet[nCurBullet]->SetSpeedX(20.0f);
			nCurBullet++;
			break;
		case GunDirection::BOTTOM:
			vFirePos.x = vPosition.x + 75;
			vFirePos.y = vPosition.y + 155;
			vFirePos.z = 0;

			pBullet[nCurBullet]->SetShot(true);
			pBullet[nCurBullet]->SetVisible(true);
			pBullet[nCurBullet]->SetGradiant(-2.5f);
			pBullet[nCurBullet]->SetPosition(vFirePos);
			pBullet[nCurBullet]->SetSpeedX(0.0f);
			nCurBullet++;
			break;
		case GunDirection::CHANGELT:
			break;
		case GunDirection::CHANGET:
			break;
		case GunDirection::CHANGELB:
			break;
		case GunDirection::CHANGEB:
			break;
		default:
			break;
		}

		fLastBullet = DXUTGetTime();
	}
	if (nCurBullet >= MAX_BULLET)
	{
		nCurBullet = 0;
	}
}

void Player::Process()
{
	UpdateCollision(54, 44, 68, 43);
	Hit();
	switch (gunDirection)
	{
	case GunDirection::IDLE:
		AniIdle();
		break;
	case GunDirection::BACK:
		break;
	case GunDirection::LITTLETOP:
		AniLittleTop();
		break;
	case GunDirection::CHANGELT:
		AniChangeLT();
		break;
	case GunDirection::TOP:
		AniTop();
		break;
	case GunDirection::CHANGET:
		AniChangeT();
		break;
	case GunDirection::LITTLEBOTTOM:
		AniLittleBottom();
		break;
	case GunDirection::CHANGELB:
		AniChangeLB();
		break;
	case GunDirection::BOTTOM:
		AniBottom();
		break;
	case GunDirection::CHANGEB:
		AniChangeB();
		break;
	}
	Shot();
	for (int i = 0; i < MAX_BULLET; i++)
	{
		pBullet[i]->Move();
	}
}

void Player::Hit()
{
	if (bHit)
	{
		fHp--;
		lastHit = DXUTGetTime();
		bHitAni = true;
		bHit = false;
	}
	if (bHitAni)
	{
		D3DCOLOR color = D3DCOLOR_COLORVALUE(1.0f, 0.5f, 0.5f, 0.8f);

		SetColor(color);
		if (DXUTGetTime() - lastHit > 0.1f)
		{
			bHitAni = false;
		}
	}
	if (!bHitAni)
	{
		D3DCOLOR color = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);

		SetColor(color);
	}
}

void Player::AniIdle()
{
	if (DXUTGetTime() - lastFrame >= 0.2f)
	{
		lastFrame = DXUTGetTime();
		SetRect(rtIdle[AniCurIdle]);
		AniCurIdle += AniCount;
	}
	if (AniCurIdle >= ANI_MOVE - 1)
	{
		AniCount = -1;
	}
	if (AniCount == -1 && AniCurIdle <= 0)
	{
		AniCount = 1;
	}
}
void Player::AniBack()
{

}

void Player::AniLittleTop()
{
	if (DXUTGetTime() - lastFrame >= 0.1f)
	{
		lastFrame = DXUTGetTime();
		SetRect(rtLittleTop[AniCurLittleTop++]);
	}
	if (AniCurLittleTop >= ANI_MOVE)
	{
		AniCurLittleTop = 0;
	}
}

void Player::AniChangeLT()
{
	if (DXUTGetTime() - lastFrame >= 0.1f)
	{
		lastFrame = DXUTGetTime();
		SetRect(rtChangeLT[AniCurChangeLT++]);
	}
	if (AniCurChangeLT >= ANI_CHANGE)
	{
		SetGunState(GunDirection::LITTLETOP);
		AniCurChangeLT = 0;
	}
}

void Player::AniTop()
{
	if (DXUTGetTime() - lastFrame >= 0.1f)
	{
		lastFrame = DXUTGetTime();
		SetRect(rtTop[AniCurTop++]);
	}
	if (AniCurTop >= ANI_MOVE)
	{
		AniCurTop = 0;
	}
}

void Player::AniChangeT()
{
	if (DXUTGetTime() - lastFrame >= 0.1f)
	{
		lastFrame = DXUTGetTime();
		SetRect(rtChangeT[AniCurChangeT++]);	
	}
	if (AniCurChangeT >= ANI_CHANGE)
	{
		SetGunState(GunDirection::TOP);
		AniCurChangeT = 0;
	}
}

void Player::AniLittleBottom()
{
	if (DXUTGetTime() - lastFrame >= 0.1f)
	{
		lastFrame = DXUTGetTime();
		SetRect(rtLittleBottom[AniCurLittleBottom++]);
	}
	if (AniCurLittleBottom >= ANI_MOVE)
	{
		AniCurLittleBottom = 0;
	}
}

void Player::AniChangeLB()
{
	if (DXUTGetTime() - lastFrame >= 0.1f)
	{
		lastFrame = DXUTGetTime();
		SetRect(rtChangeLB[AniCurChangeLB++]);
	}
	if (AniCurChangeLB >= ANI_CHANGE)
	{
		SetGunState(GunDirection::LITTLEBOTTOM);
		AniCurChangeLB = 0;
	}
}

void Player::AniBottom()
{
	if (DXUTGetTime() - lastFrame >= 0.1f)
	{
		lastFrame = DXUTGetTime();
		SetRect(rtBottom[AniCurBottom++]);
	}
	if (AniCurBottom >= ANI_MOVE)
	{
		AniCurBottom = 0;
	}
}

void Player::AniChangeB()
{
	if (DXUTGetTime() - lastFrame >= 0.1f)
	{
		lastFrame = DXUTGetTime();
		SetRect(rtChangeB[AniCurChangeB++]);
	}
	if (AniCurChangeB >= ANI_CHANGE)
	{
		SetGunState(GunDirection::BOTTOM);
		AniCurChangeB = 0;
	}
}

void Player::SetAniRect()
{
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtIdle[AniIdleCount].left = i * PLAYER_WIDTH;
		rtIdle[AniIdleCount].right = rtIdle[AniIdleCount].left + PLAYER_WIDTH;
		rtIdle[AniIdleCount].top = 0;
		rtIdle[AniIdleCount].bottom = PLAYER_HEIGHT;
		AniIdleCount++;
	}
	for (int i = 0; i < ANI_CHANGE; i++)
	{
		rtChangeLT[AniChangeLTCount].left = i * PLAYER_WIDTH;
		rtChangeLT[AniChangeLTCount].right = rtChangeLT[AniChangeLTCount].left + PLAYER_WIDTH;
		rtChangeLT[AniChangeLTCount].top = PLAYER_HEIGHT;
		rtChangeLT[AniChangeLTCount].bottom = rtChangeLT[AniChangeLTCount].top + PLAYER_HEIGHT;
		AniChangeLTCount++;
	}
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtLittleTop[AniLittleTopCount].left = i * PLAYER_WIDTH;
		rtLittleTop[AniLittleTopCount].right = rtLittleTop[AniLittleTopCount].left + PLAYER_WIDTH;
		rtLittleTop[AniLittleTopCount].top = 2 * PLAYER_HEIGHT;
		rtLittleTop[AniLittleTopCount].bottom = rtLittleTop[AniLittleTopCount].top + PLAYER_HEIGHT;
		AniLittleTopCount++;
	}
	for (int i = 0; i < ANI_CHANGE; i++)
	{
		rtChangeT[AniChangeTCount].left = i * PLAYER_WIDTH;
		rtChangeT[AniChangeTCount].right = rtChangeT[AniChangeTCount].left + PLAYER_WIDTH;
		rtChangeT[AniChangeTCount].top = 3 * PLAYER_HEIGHT;
		rtChangeT[AniChangeTCount].bottom = rtChangeT[AniChangeTCount].top + PLAYER_HEIGHT;
		AniChangeTCount++;
	}
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtTop[AniTopCount].left = i * PLAYER_WIDTH;
		rtTop[AniTopCount].right = rtTop[AniTopCount].left + PLAYER_WIDTH;
		rtTop[AniTopCount].top = 4 * PLAYER_HEIGHT;
		rtTop[AniTopCount].bottom = rtTop[AniTopCount].top + PLAYER_HEIGHT;
		AniTopCount++;
	}
	for (int i = 0; i < ANI_CHANGE; i++)
	{
		rtChangeLB[AniChangeLBCount].left = i * PLAYER_WIDTH;
		rtChangeLB[AniChangeLBCount].right = rtChangeLB[AniChangeLBCount].left + PLAYER_WIDTH;
		rtChangeLB[AniChangeLBCount].top = 5 * PLAYER_HEIGHT;
		rtChangeLB[AniChangeLBCount].bottom = rtChangeLB[AniChangeLBCount].top + PLAYER_HEIGHT;
		AniChangeLBCount++;
	}
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtLittleBottom[AniLittleBottomCount].left = i * PLAYER_WIDTH;
		rtLittleBottom[AniLittleBottomCount].right = rtLittleBottom[AniLittleBottomCount].left + PLAYER_WIDTH;
		rtLittleBottom[AniLittleBottomCount].top = 6 * PLAYER_HEIGHT;
		rtLittleBottom[AniLittleBottomCount].bottom = rtLittleBottom[AniLittleBottomCount].top + PLAYER_HEIGHT;
		AniLittleBottomCount++;
	}
	for (int i = 0; i < ANI_CHANGE; i++)
	{
		rtChangeB[AniChangeBCount].left = i * PLAYER_WIDTH;
		rtChangeB[AniChangeBCount].right = rtChangeB[AniChangeBCount].left + PLAYER_WIDTH;
		rtChangeB[AniChangeBCount].top = 7 * PLAYER_HEIGHT;
		rtChangeB[AniChangeBCount].bottom = rtChangeB[AniChangeBCount].top + PLAYER_HEIGHT;
		AniChangeBCount++;
	}
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtBottom[AniBottomCount].left = i * PLAYER_WIDTH;
		rtBottom[AniBottomCount].right = rtBottom[AniBottomCount].left + PLAYER_WIDTH;
		rtBottom[AniBottomCount].top = 8 * PLAYER_HEIGHT;
		rtBottom[AniBottomCount].bottom = rtBottom[AniBottomCount].top + PLAYER_HEIGHT;
		AniBottomCount++;
	}
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtBack[i].left = i * PLAYER_WIDTH;
		rtBack[i].right = rtBack[i].left + PLAYER_WIDTH;
		rtBack[i].top = 5 * PLAYER_HEIGHT;
		rtBack[i].bottom = rtBack[i].top + PLAYER_HEIGHT;
	}
}

void Player::CreateBullet()
{
	RECT rt;
	rt.left = 0;
	rt.right = 20;
	rt.top = 0;
	rt.bottom = 20;

	for (int i = 0; i < MAX_BULLET; i++)
	{
		pBullet[i] = new Bullet;
		pBullet[i]->SetGradiant(0);
		pBullet[i]->SetRect(rt);
	}
}