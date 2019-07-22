#include "stdafx.h"

Player::Player()
{
}

Player::Player(LPDIRECT3DTEXTURE9 texture)
{
	Create();
	SetTexture(texture);
}

Player::~Player()
{
}

void Player::Create()
{
	nFrameWidth = 140;
	nFrameHeight = 90;
	nFrameSpeed = 4;
	AniCurCount = 7;
	fMoveSpeed = 5.0f;
	nCurrentShoot = 0;
	bHit = false;
	bVisible = true;

	RECT rt;
	rt.left = 0;
	rt.right = nFrameWidth;
	rt.top = 0;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	motion = MotionState::NORMAL;

	for (int i = 0; i<8; i++){
		AniRect[i + 7].top = 0;
		AniRect[i + 7].left = (i)* nFrameWidth;
		AniRect[i + 7].right = AniRect[i + 7].left + nFrameWidth;
		AniRect[i + 7].bottom = nFrameHeight;
	}

	// AniUp
	for (int i = 0; i<7; i++){
		AniRect[6 - i].top = nFrameHeight;
		AniRect[6 - i].left = (i)* nFrameWidth;
		AniRect[6 - i].right = AniRect[6 - i].left + nFrameWidth;
		AniRect[6 - i].bottom = AniRect[6 - i].top + nFrameHeight;
	}

	SetPosition(40, 400, 0);

	CreateMissile();
}

void Player::Update()
{
	D3DXVECTOR3* pos = GetPosition();

	nMissilePointX = pos->x + nFrameWidth;
	nMissilePointY = pos->y + 25;

	if (bHit)
	{
		bHit = false;
		OBJMANAGER()->SetPlayerHP(1);
	}
}

void Player::SetMotion(MotionState state)
{
	switch (state){
	case MotionState::NORMAL:
		AniNormal();
		break;
	case MotionState::UP:
		AniUp();
		break;
	case MotionState::DOWN:
		AniDown();
		break;
	default:
		AniNormal();
		break;
	}
}

void Player::AniDown()
{
	int nTimerFrame = GATIMER()->GetAbsoluteFrame();
	static int lastFrame = 0;

	if (AniCurCount < ANICOUNT - 1){
		if (lastFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed){
			SetRect(AniRect[AniCurCount++]);
			lastFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
	}
}

void Player::AniUp()
{
	int nTimerFrame = GATIMER()->GetAbsoluteFrame();
	static int lastFrame = 0;

	if (AniCurCount >= 0){
		if (lastFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed){
			SetRect(AniRect[AniCurCount--]);
			lastFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
	}

}

void Player::AniNormal()
{
	int nTimerFrame = GATIMER()->GetAbsoluteFrame();
	static int lastFrame = 0;

	if (AniCurCount != 7){
		if (lastFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed){
			if (AniCurCount > 7){
				SetRect(AniRect[--AniCurCount]);
			}
			else if (AniCurCount < 7){
				SetRect(AniRect[++AniCurCount]);
			}
			lastFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
	}

}

// 주인공 움직임
void Player::Move(MotionState motion)
{
	switch (motion){
	case MotionState::UP: // 위
		this->vPosition.y -= fMoveSpeed; // 위로 이동
		if (vPosition.y < 0){ // 화면밖으로 나가지 않게 설정
			vPosition.y = 0;
		}
		break;
	case MotionState::DOWN: // 아래
		this->vPosition.y += fMoveSpeed; // 아래로 이동
		if (vPosition.y + nFrameHeight > 768){ // 화면밖으로 나가지 않게 설정
			vPosition.y = 768 - nFrameHeight;
		}
		break;
	case MotionState::LEFT: // 왼쪽
		this->vPosition.x -= fMoveSpeed; // 왼쪽으로 이동
		if (vPosition.x < 0){ // 화면밖으로 나가지 않게 설정
			vPosition.x = 0;
		}
		break;
	case MotionState::RIGHT: // 오른쪽
		this->vPosition.x += fMoveSpeed; // 오른쪽으로 이동
		if (vPosition.x + nFrameWidth > 1024){ // 화면밖으로 나가지 않게 설정
			vPosition.x = 1024 - nFrameWidth;
		}
		break;
	}
}

void Player::CreateMissile()
{
	nMissileCount = 100;
	for (int i = 0; i < nMissileCount; i++)
	{
		m_pMissile[i] = new Missile(OBJMANAGER()->GetTexture(GaBase::TextureID::MISSILE), 80, 15);

		RECT rt;
		rt.top = 0;
		rt.left = 0;
		rt.right = 80;
		rt.bottom = 15;

		m_pMissile[i]->SetRect(rt);
	}
}

void Player::Shot(DWORD absoluteFrame)
{
	if (absoluteFrame - nCurAbsoluteFrame > 7)
	{
		m_pMissile[nCurrentShoot]->SetShoot(true);
		m_pMissile[nCurrentShoot]->SetVisible(true);
		m_pMissile[nCurrentShoot]->SetStartPoint(nMissilePointX, nMissilePointY);

		nCurrentShoot++;
		
		if (nCurrentShoot >= nMissileCount)
		{
			nCurrentShoot = 0;
		}

		nCurAbsoluteFrame = absoluteFrame;
	}
}