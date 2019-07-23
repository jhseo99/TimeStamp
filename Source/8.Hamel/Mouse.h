#pragma once
class Mouse
{
public:
	Mouse();
	~Mouse();

	static Mouse* Instance() { return &singleton; }

public:
	static Mouse singleton;

	bool m_bCurrentClickLeft;
	bool m_bBeforeClickLeft;

	bool m_bCurrentClickRight;
	bool m_bBeforeClickRight;

	float m_fCursorPosX;
	float m_fCursorPosY;

	float m_fMouseX;
	float m_fMouseY;

	int m_nGameX;
	int m_nGameY;

	bool m_bCameraeMove;

	float m_fSensitivity;

public:
	void Init();
};

#define MOUSE() Mouse::Instance()