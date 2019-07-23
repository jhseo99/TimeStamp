#include "stdafx.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR lpszParam, int nCmdShow)
{
	int returnValue;

	GAAPP()->Init(hInstance, lpszParam, nCmdShow);
	returnValue = GAAPP()->Run();

	return returnValue;
}