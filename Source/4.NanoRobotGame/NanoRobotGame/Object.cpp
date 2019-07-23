#include "stdafx.h"


Object::Object()
	:d3dColor(0),
	pTexture(NULL),
	bVisible(false)
{
	ZeroMemory(&rtSize, sizeof(rtSize));
	ZeroMemory(&vPosition, sizeof(vPosition));
	ZeroMemory(&vCenter, sizeof(vCenter));
	d3dColor = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);
}


Object::~Object()
{
}

void Object::Process()
{
}

void Object::Render(LPD3DXSPRITE sprite)
{
	if (bVisible)
	{
		sprite->Draw(GetTexture(), GetRect(), GetCenter(), GetPosition(), GetColor());
	}
}

void Object::SetCollisonRect(int left, int right, int top, int bottom)
{
	rtCollison.left = vPosition.x + left;
	rtCollison.top = vPosition.y + right;
	rtCollison.right = rtCollison.left + top;
	rtCollison.bottom = rtCollison.top + bottom;
}

void Object::CollisonCheck(Object* object)
{
	if (this->bVisible
		&& object->GetVisible()
		&& vPosition.x < 1024
		&& !bHit
		&& !object->GetHit())
	{
		if (rtCollison.left > object->GetCollisonRect()->right || rtCollison.right < object->GetCollisonRect()->left ||
			rtCollison.top > object->GetCollisonRect()->bottom || rtCollison.bottom < object->GetCollisonRect()->top)
		{
		}
		else
		{
			this->bHit = true;
			object->SetHit(true);
		}
	}
}


void Object::Destroy()
{
	delete this;
}