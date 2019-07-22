#pragma once

#define MOUSE_BUFFER_SIZE 16

class GaMouse
{
public:
	GaMouse(void);
	~GaMouse(void);

protected:
	LPDIRECTINPUTDEVICE8 lpDInputDevice;
	DIDEVICEOBJECTDATA chMouseBuffer[MOUSE_BUFFER_SIZE];
	bool bClicked;

public:
	void Init(HWND hWnd);
	void Acquire();
	BOOL Update();
	BOOL IsButtonDown(DWORD dwButton);
	BOOL IsButtonUp(DWORD dwButton);
	BOOL IsButtonClick(DWORD dwButton);

	LPDIRECTINPUTDEVICE8 GetDevice() { return lpDInputDevice; }
};