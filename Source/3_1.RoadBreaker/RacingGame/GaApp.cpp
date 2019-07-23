#include "stdafx.h"

GaApp GaApp::singleton;

GaApp::GameMode GaApp::gamemode = GaApp::GameMode::INTRO;

int GaApp::nScreenWidth = 1024;
int GaApp::nScreenHeight = 768;

bool GaApp::bBeforeClick = false;
bool GaApp::bCurrentClick = false;

GaApp::GaApp()
{
}

GaApp::~GaApp()
{
	Release();
}

void GaApp::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASS wcex;

	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"RoadBreaker";
	
	RegisterClass(&wcex);

	this->hInstance = hInstance;

	hWnd = CreateWindow(L"RoadBreaker", L"RoadBreaker", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, nScreenWidth, nScreenHeight, NULL, NULL, hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);

	nBeforeLastFrame = GATIMER()->GetAbsoluteFrame();
}

HRESULT GaApp::InitD3D()
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = nScreenWidth;
	d3dpp.BackBufferHeight = nScreenHeight;

	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &pd3dDevice)))
	{
		return E_FAIL;
	}

	D3DXCreateSprite(pd3dDevice, &pSprite);

	D3DXCreateFont(pd3dDevice, 55, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH || FF_DONTCARE, TEXT("Courier"), &Font);

	OBJMANAGER()->Create();

	return S_OK;
}

void GaApp::Render()
{
	pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0.0f);

	pd3dDevice->BeginScene();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	switch (gamemode)
	{
	case GaApp::GameMode::INTRO:
		OBJMANAGER()->IntroRender(pSprite);
		break;
	case GaApp::GameMode::MENU:
		OBJMANAGER()->MenuRender(pSprite);
		break;
	case GaApp::GameMode::CHOOSE:
		OBJMANAGER()->ChooseRender(pSprite);
		break;
	case GaApp::GameMode::STAGE1:
		OBJMANAGER()->Stage1Render(pSprite);
		break;
	case GaApp::GameMode::STAGE2:
		OBJMANAGER()->Stage2Render(pSprite);
		break;
	case GaApp::GameMode::STAGE3:
		OBJMANAGER()->Stage3Render(pSprite);
		break;
	case GaApp::GameMode::ENDING:
		OBJMANAGER()->EndingRedner(pSprite);
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
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			gamemode = GaApp::GameMode::MENU;
			OBJMANAGER()->Reset();
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		bCurrentClick = true;
		break;
	case WM_LBUTTONUP:
		bBeforeClick = false;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

int GaApp::Run()
{
	if (FAILED(InitD3D()))
	{
		return 0;
	}

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			GATIMER()->Update();

			if (nBeforeLastFrame - GATIMER()->GetAbsoluteFrame() >= 1)
			{
				OBJMANAGER()->PrcessAll();
				OBJMANAGER()->KeyProc();
				OBJMANAGER()->MouseProc();
				Render();

				bCurrentClick = bBeforeClick;
				nBeforeLastFrame = GATIMER()->GetAbsoluteFrame();
			}
		}
	}

	return (int)msg.wParam;
}

void GaApp::Release()
{
	if (pD3D != NULL) pD3D->Release();
	if (pd3dDevice != NULL) pd3dDevice->Release();
	if (pSprite != NULL) pSprite->Release();
}