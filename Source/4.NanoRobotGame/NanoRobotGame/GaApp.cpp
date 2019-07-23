#include "stdafx.h"

GaApp GaApp::singleton;

int GaApp::nScreenWidth = 1024;
int GaApp::nScreenHeight = 768;

bool GaApp::bClick = false;

GaApp::GaApp()
	:nBeforeFrame(0),
	gamemode(INTRO)
{
}


GaApp::~GaApp()
{
	Release();
}

void GaApp::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"NanoRobotGame";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wcex);
	
	// Create window
	// 인스턴스 핸들 지정
	this->hInstance = hInstance;

	hWnd = CreateWindow(L"NanoRobotGame", L"NanoRobotGame", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, nScreenWidth, nScreenHeight, NULL, NULL, hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);

	nBeforeFrame = GATIMER()->GetAbsoluteFrame();
}

HRESULT GaApp::InitD3D()
{
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = nScreenWidth;
	d3dpp.BackBufferHeight = nScreenHeight;

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_pd3dDevice)))
	{
		return E_FAIL;
	}

	D3DXCreateSprite(m_pd3dDevice, &m_pSprite);
	D3DXCreateFont(m_pd3dDevice, 80, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH || FF_DONTCARE, TEXT("Courier"), &Font);

	OBJMANAGER()->Create();

	return S_OK;
}

void GaApp::Render()
{
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	if (SUCCEEDED(m_pd3dDevice->BeginScene()))
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		switch (gamemode)
		{
		case GaApp::GameMode::INTRO:
		case GaApp::GameMode::MENU:
			OBJMANAGER()->MainRender(m_pSprite);
			break;
		case GaApp::GameMode::STAGE1:
			OBJMANAGER()->Stage1Render(m_pSprite);
			break;
		case GaApp::GameMode::STAGE2:
			OBJMANAGER()->Stage2Render(m_pSprite);
			break;
		case GaApp::GameMode::DIE:
			OBJMANAGER()->DieRender(m_pSprite);
			break;
		case GaApp::GameMode::ENDING:
			OBJMANAGER()->EndingRender(m_pSprite);
			break;
		}

		m_pSprite->End();
		m_pd3dDevice->EndScene();
	}

	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

int GaApp::Run()
{
	if (FAILED(InitD3D()))
	{
		return 0;
	}

	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		// 종료
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			GATIMER()->Update();

			if (nBeforeFrame - GATIMER()->GetAbsoluteFrame() >= 1)
			{
				OBJMANAGER()->ProcessAll();
				OBJMANAGER()->KeyProc();
				OBJMANAGER()->MouseProc();
				Render();

				nBeforeFrame = GATIMER()->GetAbsoluteFrame();
			}
		}
	}

	return (int)msg.wParam;
}

void GaApp::Release()
{
	if (m_pd3dDevice != NULL)
		m_pd3dDevice->Release();

	if (m_pD3D != NULL)
		m_pD3D->Release();

	if (m_pSprite != NULL)
		m_pSprite->Release();
}

LRESULT GaApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ACTIVATE:
		break;
	case WM_LBUTTONDOWN:
		bClick = true;
		break;
	case WM_LBUTTONUP:
		bClick = false;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
