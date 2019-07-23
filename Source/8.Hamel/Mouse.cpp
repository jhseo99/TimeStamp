#include "DXUT.h"
#include "Mouse.h"

Mouse Mouse::singleton;

Mouse::Mouse()
{
	Init();
}


Mouse::~Mouse()
{
}

void Mouse::Init()
{
	m_bCurrentClickLeft = false;
	m_bBeforeClickLeft = false;

	m_bCurrentClickRight = false;
	m_bBeforeClickRight = false;

	m_fCursorPosX = 0.0f;
	m_fCursorPosY = 0.0f;

	m_fMouseX = 0.0f;
	m_fMouseY = 0.0f;

	m_nGameX = 0;
	m_nGameY = 0;

	m_bCameraeMove = false;

	m_fSensitivity = 15.0f;
}