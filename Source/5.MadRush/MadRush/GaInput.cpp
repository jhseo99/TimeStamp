#include "stdafx.h"

GaInput GaInput::singleton;

GaInput::GaInput(void)
{
	lpDInput = NULL;
}

GaInput::~GaInput(void)
{
	if (lpDInput != NULL)
	{
		lpDInput->Release();
		lpDInput = NULL;
	}
}

void GaInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&lpDInput,
		NULL);

	m_Keyboard.Init(hWnd);
	m_Mouse.Init(hWnd);
}

void GaInput::Activated()
{
	if (m_Keyboard.GetDevice() != NULL)
	{
		m_Keyboard.Acquire();
		m_Mouse.Acquire();
	}
}