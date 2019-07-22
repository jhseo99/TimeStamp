#include "stdafx.h"

Object::Object(void)
	:d3dColor(0),
	pTexture(NULL),
	bVisible(false)
{
	ZeroMemory(&rtSize, sizeof(rtSize));
	ZeroMemory(&vCenter, sizeof(vCenter));
	ZeroMemory(&vPosition, sizeof(vPosition));
	d3dColor = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);
}

Object::~Object(void)
{
}

void Object::Create()
{
}

void Object::Process()
{

}

void Object::Render(LPD3DXSPRITE sprite)
{
	if (bVisible == true)
	{
		sprite->Draw(GetTexture(), GetRect(), GetCenter(), GetPosition(), GetColor());
	}
}

void Object::SetCollison(int left, int right, int top, int bottom)
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
		&& vPosition.y > 0 - this->nFrameHeight
		&& !bHit
		&& !object->GetHit())
	{
		if (rtCollison.left > object->GetCollsonRect()->right || rtCollison.right < object->GetCollsonRect()->left ||
			rtCollison.top > object->GetCollsonRect()->bottom || rtCollison.bottom < object->GetCollsonRect()->top)
		{
		}
		else
		{
			this->bHit = true;
			object->SetHit(true);
		}
	}
}

void Object::ItemCollisonCheck(Object* object)
{
	if (this->bVisible
		&& object->GetVisible()
		&& vPosition.y > 0 - this->nFrameHeight
		&& !bHit
		&& !object->GetHit())
	{
		if (rtCollison.left > object->GetCollsonRect()->right || rtCollison.right < object->GetCollsonRect()->left ||
			rtCollison.top > object->GetCollsonRect()->bottom || rtCollison.bottom < object->GetCollsonRect()->top)
		{
		}
		else
		{
			this->bHit = true;
		}
	}
}

void Object::Destroy()
{
	delete this;
}