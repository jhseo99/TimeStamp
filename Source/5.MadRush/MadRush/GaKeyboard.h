#pragma once

class GaKeyboard
{
public:
	GaKeyboard(void);
	~GaKeyboard(void);

protected:
	LPDIRECTINPUTDEVICE8 lpDInputDevice;
	BYTE byteKeyBuffer[256];

public:
	void Init(HWND hWnd);
	void Acquire();
	void Update();

	LPDIRECTINPUTDEVICE8 GetDevice() { return lpDInputDevice; }

public:
	BOOL IsButtonDown(int nButton);
	BOOL IsButtonUp(int nButton);
	BOOL IsAnyButtonDown();
};