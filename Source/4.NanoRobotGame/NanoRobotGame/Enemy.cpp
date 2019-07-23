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
		case MotionState::UP: // ��
			this->vPosition.y -= fMoveSpeed / 3; // ���� �̵�
			if (vPosition.y < 0){ // ȭ������� ������ �ʰ� ����
				vPosition.y = 0;
			}
			break;
		case MotionState::DOWN: // �Ʒ�
			this->vPosition.y += fMoveSpeed / 3; // �Ʒ��� �̵�
			if (vPosition.y + nFrameHeight > 768){ // ȭ������� ������ �ʰ� ����
				vPosition.y = 768 - nFrameHeight;
			}
			break;
		case MotionState::LEFT: // ����
			this->vPosition.x -= fMoveSpeed; // �������� �̵�
			break;
		case MotionState::RIGHT: // ������
			this->vPosition.x += fMoveSpeed; // ���������� �̵�
			if (vPosition.x + nFrameWidth > 1024){ // ȭ������� ������ �ʰ� ����
				vPosition.x = 1024 - nFrameWidth;
			}
			break;
		}
	}
}