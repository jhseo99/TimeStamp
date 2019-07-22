#pragma once

class GaInput
{
public:
	~GaInput(void);

	static GaInput* Instance() { return &singleton; }

private:
	GaInput(void);

	static GaInput singleton;

	LPDIRECTINPUT8 lpDInput;
	GaKeyboard m_Keyboard;
	GaMouse m_Mouse;

public:
	void Init(HINSTANCE hInstance, HWND hWnd);
	void Activated();

	LPDIRECTINPUT8 GetInput() { return lpDInput; }
	GaKeyboard* GetKeyboard() { return &m_Keyboard; }
	GaMouse* GetMouse() { return &m_Mouse; }
};

#define GAINPUT() GaInput::Instance()