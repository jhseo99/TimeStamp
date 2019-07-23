#include "stdafx.h"

GaKeyboard::GaKeyboard(void)
{
	lpDInputDevice = NULL;
	ZeroMemory(&byteKeyBuffer, sizeof(TCHAR) * 256);
}

GaKeyboard::~GaKeyboard(void)
{
	if (lpDInputDevice != NULL)
	{
		lpDInputDevice->Release();
		lpDInputDevice = NULL;
	}
}

void GaKeyboard::Init(HWND hWnd)
{
	GAINPUT()->GetInput()->CreateDevice(GUID_SysKeyboard, &lpDInputDevice, NULL);

	lpDInputDevice->SetDataFormat(&c_dfDIKeyboard);
	lpDInputDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	lpDInputDevice->Acquire();
}

void GaKeyboard::Update()
{
	HRESULT hRet;

	hRet = lpDInputDevice->GetDeviceState(sizeof(byteKeyBuffer), (LPVOID)&byteKeyBuffer);

	if (FAILED(hRet) && hRet == DIERR_INPUTLOST)
	{
		return;
	}
}

BOOL GaKeyboard::IsButtonDown(int nButton)
{
	if (byteKeyBuffer[nButton] & 0x80)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL GaKeyboard::IsButtonUp(int nButton)
{
	if (!(byteKeyBuffer[nButton] & 0x80))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


BOOL GaKeyboard::IsAnyButtonDown()
{
	BOOL bKeyDowned = FALSE;

	for (int i = 0; i < 256; i++)
	{
		if (byteKeyBuffer[i] & 0x80)
		{
			bKeyDowned = TRUE;
		}
	}

	return bKeyDowned;
}


void GaKeyboard::Acquire()
{
	lpDInputDevice->Acquire();
}