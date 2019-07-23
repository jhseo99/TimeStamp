#include "stdafx.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::AniMove()
{

}

void Enemy::Move(MotionState state)
{
	if (!bDie && bVisible)
	{
		switch (state){
		case MotionState::UP: // 위
			this->vPosition.y -= fMoveSpeed / 3; // 위로 이동
			if (vPosition.y < 0){ // 화면밖으로 나가지 않게 설정
				vPosition.y = 0;
			}
			break;
		case MotionState::DOWN: // 아래
			this->vPosition.y += fMoveSpeed / 3; // 아래로 이동
			if (vPosition.y + nFrameHeight > 768){ // 화면밖으로 나가지 않게 설정
				vPosition.y = 768 - nFrameHeight;
			}
			break;
		case MotionState::LEFT: // 왼쪽
			this->vPosition.x -= fMoveSpeed; // 왼쪽으로 이동
			break;
		case MotionState::RIGHT: // 오른쪽
			this->vPosition.x += fMoveSpeed; // 오른쪽으로 이동
			if (vPosition.x + nFrameWidth > 1024){ // 화면밖으로 나가지 않게 설정
				vPosition.x = 1024 - nFrameWidth;
			}
			break;
		}
	}
}