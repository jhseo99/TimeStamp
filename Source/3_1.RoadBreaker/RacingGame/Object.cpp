#include "stdafx.h"

Object::Object()
	:d3dColor(0),
	pTexture(NULL),
	bVisible(false)
{
	ZeroMemory(&rtSize, sizeof(rtSize));
	ZeroMemory(&vPostion, sizeof(vPostion));
	ZeroMemory(&vCenter, sizeof(vCenter));
	d3dColor = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);
}

Object::~Object()
{
}

void Object::Create()
{
}

void Object::Render(LPD3DXSPRITE sprite)
{
	if (bVisible)
	{
		sprite->Draw(GetTexture(), GetRect(), GetPosition(), GetCenter(), GetColor());
	}
}

void Object::SetCollisionRect(int left, int right, int top, int bottom)
{
	rtCollision.left = vPostion.x + left;
	rtCollision.top = vPostion.y + right;
	rtCollision.right = rtCollision.left - top;
	rtCollision.bottom = rtCollision.top - bottom;
}

void Object::CollisionCheck(Object* object)
{
	if (this->bVisible
		&& object->GetVisible()
		&& !bHit
		&& !object->GetHit())
	{
		if (rtCollision.left < object->GetCollisionRect()->right || rtCollision.right > object->GetCollisionRect()->left ||
			rtCollision.top < object->GetCollisionRect()->bottom || rtCollision.bottom > object->GetCollisionRect()->top)
		{
		}
		else
		{
			this->bHit = true;
			object->SetHit(true);

			vDirection.x = object->GetPosition()->x - vPostion.x;
			vDirection.y = object->GetPosition()->y - vPostion.y;

			D3DXVec2Normalize(&vDirection, &vDirection);

			vDirection = -vDirection;

			D3DXVECTOR2 vec;

			vec.x = vPostion.x - object->GetPosition()->x;
			vec.y = vPostion.y - object->GetPosition()->y;

			D3DXVec2Normalize(&vec, &vec);

			vec = -vec;

			object->SetDirection(vec);
		}
	}
}

void Object::HitProcess()
{
	if (bHit)
	{
		vPostion.x += (vDirection.x * 30.0f);
		fSpeed -= 20.0f;

		bHit = false;
	}
}

void Object::Destroy()
{
	delete this;
}