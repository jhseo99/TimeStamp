#include "stdafx.h"

GaApp GaApp::singleton;

int GaApp::nScreenWidth = 1024;
int GaApp::nScreenHeight = 768;

GaApp::GaApp(void)
	:lpszClass(TEXT("MadRush")),
	mode(GameMode(INTRO)),
	nBeforeFrame(0),
	Font(NULL)
{
}

GaApp::~GaApp(void)
{
	Release();
}

void GaApp::Init(HINSTANCE hInstance, LPSTR lpszParam, int nCmdShow)
{
	WNDCLASS WndClass;

	this->hInstance = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDC_APPSTARTING);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		nScreenWidth, nScreenHeight,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);

	GAINPUT()->Init(hInstance, hWnd);
	nBeforeFrame = GATIMER()->GetAbsoluteFrame();
}

HRESULT GaApp::InitD3D()
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = nScreenWidth;
	d3dpp.BackBufferHeight = nScreenHeight;

	pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&pd3dDevice);

	D3DXCreateSprite(pd3dDevice, &pSprite);

	D3DXCreateFont(pd3dDevice, 70, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH || FF_DONTCARE, TEXT("Buxton Sketch"), &Font);

	OBJMANAGER()->Create();

	return S_OK;
}
void GaApp::Render()
{
	pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f);

	pd3dDevice->BeginScene();

	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	switch (mode)
	{
	case GameMode::INTRO:
		OBJMANAGER()->IntroRender(pSprite);
		break;
	case GameMode::GAME1:
		OBJMANAGER()->Stage1Render(pSprite);
		break;
	case GameMode::GAME2:
		OBJMANAGER()->Stage2Render(pSprite);
		break;
	case GameMode::DIE:
		OBJMANAGER()->Stage1Render(pSprite);
		OBJMANAGER()->DieRender(pSprite);
		break;
	case GameMode::ENDING:
		OBJMANAGER()->EndingRender(pSprite);
		break;
	}

	pSprite->End();

	pd3dDevice->EndScene();
	pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

LRESULT GaApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ACTIVATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

int GaApp::Run()
{
	MSG Message;
	ZeroMemory(&Message, sizeof(Message));

	if (SUCCEEDED(InitD3D()))
	{
		while (Message.message != WM_QUIT)
		{
			if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
			else
			{
				GATIMER()->Update();

				if (nBeforeFrame - GATIMER()->GetAbsoluteFrame() >= 1)
				{
					GATIMER()->Timer();
					OBJMANAGER()->KeyProc();
					OBJMANAGER()->MouseProc();
					OBJMANAGER()->ProcessAll();
					nBeforeFrame = GATIMER()->GetAbsoluteFrame();
				}

				Render();
			}
		}
	}

	return (int)Message.wParam;
}

void GaApp::Release()
{
	if (pD3D != NULL)
	{
		pD3D->Release();
	}
	if (pSprite != NULL)
	{
		pSprite->Release();
	}
	if (pd3dDevice != NULL)
	{
		pd3dDevice->Release();
	}
}