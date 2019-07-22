#include "stdafx.h"

GaMouse::GaMouse(void)
{
	lpDInputDevice = NULL;
	bClicked = false;
	ZeroMemory(chMouseBuffer, sizeof(TCHAR) * 256);
}

GaMouse::~GaMouse(void)
{
	if (lpDInputDevice != NULL)
	{
		lpDInputDevice->Release();
		lpDInputDevice = NULL;
	}
}

void GaMouse::Init(HWND hWnd)
{
	GAINPUT()->GetInput()->CreateDevice(GUID_SysMouse, &lpDInputDevice, NULL);

	lpDInputDevice->SetDataFormat(&c_dfDIMouse);
	lpDInputDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;

	dipdw.dwData = MOUSE_BUFFER_SIZE;

	lpDInputDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	lpDInputDevice->Acquire();
}

BOOL GaMouse::Update()
{
	HRESULT hRet;

	ZeroMemory(chMouseBuffer, sizeof(DIDEVICEOBJECTDATA) * MOUSE_BUFFER_SIZE);

	for (int i = 0; i < MOUSE_BUFFER_SIZE; i++)
	{
		DWORD element = 1;

		hRet = lpDInputDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &chMouseBuffer[i], &element, 0);

		if ((FAILED(hRet)) && hRet == DIERR_INPUTLOST)
		{
			lpDInputDevice->Acquire();

			if (FAILED(lpDInputDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &chMouseBuffer[i], &element, 0)))
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}


	return TRUE;
}

void GaMouse::Acquire()
{
	lpDInputDevice->Acquire();
}

BOOL GaMouse::IsButtonDown(DWORD dwButton)
{
	DWORD dwElements;

	for (dwElements = 0; dwElements < 8; dwElements++)
	{
		if (chMouseBuffer[dwElements].dwOfs == dwButton)
		{
			if (chMouseBuffer[dwElements].dwData & 0x80)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL GaMouse::IsButtonUp(DWORD dwButton)
{
	DWORD dwElements;

	for (dwElements = 0; dwElements < 8; dwElements++)
	{
		if (chMouseBuffer[dwElements].dwOfs == dwButton)
		{
			if (!(chMouseBuffer[dwElements].dwData & 0x80))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL GaMouse::IsButtonClick(DWORD dwButton)
{
	if (bClicked)
	{
		if (IsButtonUp(dwButton))
		{
			bClicked = false;
			return TRUE;
		}
	}

	if (IsButtonDown(dwButton))
	{
		if (!bClicked)
		{
			bClicked = true;
		}
	}

	return FALSE;
}