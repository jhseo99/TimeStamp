#include <d3d9.h>
#include <d3dx9.h>
#include <stdlib.h>
#include <Windows.h>
#include <strsafe.h>
#include <time.h>
#pragma comment (lib, "winmm.lib")

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
LPD3DXFONT Fonts = NULL;

LPD3DXSPRITE g_pSprite;
WNDCLASSEX g_wc;
HWND g_hwnd;

//VecScreen
D3DXVECTOR3 ScreenVec;
D3DXVECTOR3 Map1Vec;
D3DXVECTOR3 Map2Vec;

//Rect
RECT ScreenRect;

ID3DXFont* Font;

//Animation
float Anitime = 0.0f;

//button
bool beforeClick = false;
bool currentClick = false;
int g_MouseX = 0;
int g_MouseY = 0;

//Speed
float Speed = 15.0f;
float MaxSpeed = 30.0f;

//Text
char Name_spdStr[1000];
char SpeedStr[1000];

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT InitD3D(HWND hWnd);

//ScreenState
enum Screen
{
	Intro,
	Main,
	Choice,
	Game1,
};
Screen currentScreen = Intro;

struct Texture
{
	LPDIRECT3DTEXTURE9 Tex = NULL;
	D3DXVECTOR3 Vec;
	RECT rc_Rect;
	BOOL Visible;
};
Texture g_pIntro;
Texture g_pIntro_off;
Texture g_pTitle;
Texture g_pMain;
Texture g_pStart;
Texture g_pExplan;
Texture g_pRank;
Texture g_pExit;
Texture g_pExit_Yes;
Texture g_pExit_No;
Texture g_pChoice;
Texture g_pCloude1;
Texture g_pCloude2;
Texture g_pBack_For1;
Texture g_pBack_For2;
Texture g_pCar;

void InitWin(void)
{
	WNDCLASSEX g_wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"D3D Tutorial", NULL };
	RegisterClassEx(&g_wc);

	g_hwnd = CreateWindow("D3D Tutorial", "Game",
		WS_OVERLAPPED, 0, 0, 800, 600,
		GetDesktopWindow(), NULL, g_wc.hInstance, NULL);
}

void InitDX(void)
{
	ShowCursor(TRUE);

	InitD3D(g_hwnd);
	D3DXCreateSprite(g_pd3dDevice, &g_pSprite);

	//Screen Rect
	ScreenRect.right = 800;
	ScreenRect.bottom = 600;

	//rect
	g_pCar.rc_Rect.right = 80;
	g_pCar.rc_Rect.bottom = 150;

	g_pTitle.rc_Rect.right = 231;
	g_pTitle.rc_Rect.bottom = 91;

	//Screen Vector
	ScreenVec.x = 0.0f;
	ScreenVec.y = 0.0f;

	//VecPos
	g_pIntro_off.Vec.x = 0.0f;
	g_pIntro_off.Vec.y = 0.0f;

	g_pCloude1.Vec.x = 0.0f;
	g_pCloude1.Vec.y = 0.0f;

	g_pCloude2.Vec.x = 800.0f;
	g_pCloude2.Vec.y = 0.0f;

	Map1Vec.x = 0.0f;
	Map1Vec.y = 0.0f;

	Map2Vec.x = 0.0f;
	Map2Vec.y = -600.0f;

	g_pCar.Vec.x = 360.0f;
	g_pCar.Vec.y = 400.0f;

	g_pTitle.Vec.x = 280;
	g_pTitle.Vec.y = 98;

	D3DXCreateFont(g_pd3dDevice, 30, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "OCR A Std", &Font);
}

void LoadData(void)
{
	D3DXCreateTextureFromFile(g_pd3dDevice, "Intro1.png", &g_pIntro.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Intro2.png", &g_pIntro_off.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Main.png", &g_pMain.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Title.png", &g_pTitle.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Choice.png", &g_pChoice.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Start.png", &g_pStart.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Explan.png", &g_pExplan.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Rank.png", &g_pRank.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Exit.png", &g_pExit.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Exit_Yes.png", &g_pExit_Yes.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Exit_No.png", &g_pExit_No.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Cloude1.png", &g_pCloude1.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Cloude2.png", &g_pCloude2.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Back_For.png", &g_pBack_For1.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "p_car.png", &g_pCar.Tex);
}

HRESULT InitD3D(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = 800;
	d3dpp.BackBufferHeight = 600;

	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice);

	return S_OK;
}

VOID Cleanup()
{
	if (g_pSprite != NULL)
		g_pSprite->Release();

	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}

void Initilize(void)
{
	InitWin();
	InitDX();
	LoadData();

	// Show the window
	ShowWindow(g_hwnd, SW_SHOWDEFAULT);
	UpdateWindow(g_hwnd);
}

void IntroUpdate()
{
	g_pCloude1.Vec.x -= 0.5f;
	g_pCloude2.Vec.x -= 0.5f;

	if (g_pCloude1.Vec.x <= -800)
	{
		g_pCloude1.Vec.x = 800.0f;
	}
	else if (g_pCloude2.Vec.x <= 0)
	{
		g_pCloude1.Vec.x += 0.5f;
		g_pCloude2.Vec.x += 0.5f;
	}

	Anitime += 0.5f;
	if (Anitime >= 0 && Anitime < 10)
	{
		g_pIntro.Visible = TRUE;
		g_pIntro_off.Visible = FALSE;
	}
	else if (Anitime > 20)
	{
		g_pIntro_off.Visible = TRUE;
		g_pIntro.Visible = FALSE;

		if (Anitime > 30)
		{
			Anitime = 0.0f;
		}
	}

	if (beforeClick == true && currentClick == false)
	{
		currentScreen = Main;
	}
}

void MainUpdate()
{
	if (beforeClick == true && currentClick == false)
	{
		if (g_MouseX >= 38 && g_MouseX <= 230 &&
			g_MouseY >= 52 && g_MouseY <= 110)
		{
			g_pStart.Visible = TRUE;
			g_pExplan.Visible = FALSE;
			g_pRank.Visible = FALSE;
			g_pExit.Visible = FALSE;

			currentScreen = Game1;
		}
		else if (g_MouseX >= 38 && g_MouseX <= 230 &&
				g_MouseY >= 128 && g_MouseY <= 183)
		{
			g_pStart.Visible = FALSE;
			g_pExplan.Visible = TRUE;
			g_pRank.Visible = FALSE;
			g_pExit.Visible = FALSE;
		}
		else if (g_MouseX >= 38 && g_MouseX <= 230 &&
			g_MouseY >= 199 && g_MouseY <= 260)
		{
			g_pStart.Visible = FALSE;
			g_pExplan.Visible = FALSE;
			g_pRank.Visible = TRUE;
			g_pExit.Visible = FALSE;
		}
		else if (g_MouseX >= 38 && g_MouseX <= 230 &&
			g_MouseY >= 275 && g_MouseY <= 334)
		{
			g_pStart.Visible = FALSE;
			g_pExplan.Visible = FALSE;
			g_pRank.Visible = FALSE;
			g_pExit.Visible = TRUE;
		}
	}
	if (g_pExit.Visible == TRUE)
	{
		POINT Pos;

		GetCursorPos(&Pos);
		
		if (Pos.x >= 312 && Pos.x <= 482 &&
			Pos.y >= 226 && Pos.y <= 270)
		{
			g_pExit_Yes.Visible = TRUE;
			g_pExit_No.Visible = FALSE;

			if (beforeClick == true && currentClick == false)
			{
				Cleanup();
				PostQuitMessage(0);
			}
		}
		else if (Pos.x >= 498 && Pos.x <= 666 &&
				Pos.y >= 226 && Pos.y <= 270)
		{
			g_pExit_Yes.Visible = FALSE;
			g_pExit_No.Visible = TRUE;
		}
		else
		{
			g_pExit_Yes.Visible = FALSE;
			g_pExit_No.Visible = FALSE;
		}
	}
}

void ChoiceUpdate()
{

}

void GameUpdate()
{
	ShowCursor(FALSE);

	Speed -= 0.02f;
	//Move
	if (GetAsyncKeyState(VK_UP))
	{
		Speed += 0.07f;

		if (GetAsyncKeyState(VK_RIGHT))
		{
			g_pCar.Vec.x += 2.5f;
		}
		else if (GetAsyncKeyState(VK_LEFT))
		{
			g_pCar.Vec.x -= 2.5f;
		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			Speed -= 0.5f;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) && Speed != 0)
	{
		g_pCar.Vec.x += 2.5f;

		if (GetAsyncKeyState(VK_UP))
		{
			Speed += 0.07f;
		}

		if (GetAsyncKeyState(VK_SPACE))
		{
			Speed -= 0.5f;
		}
	}
	else if (GetAsyncKeyState(VK_LEFT) && Speed != 0)
	{
		g_pCar.Vec.x -= 2.5f;

		if (GetAsyncKeyState(VK_UP))
		{
			Speed += 0.07f;
		}

		if (GetAsyncKeyState(VK_SPACE))
		{
			Speed -= 0.5f;
		}
	}
	else if (GetAsyncKeyState(VK_SPACE))
	{
		Speed -= 0.5f;
	}

	if (g_pCar.Vec.x <= 130)
	{
		g_pCar.Vec.x = 130.0f;
	}
	else if (g_pCar.Vec.x + g_pCar.rc_Rect.right >= 664)
	{
		g_pCar.Vec.x = 664.0f - g_pCar.rc_Rect.right;
	}

	//MaxSpeed
	if (Speed >= MaxSpeed)
	{
		Speed = MaxSpeed;
	}

	if (Speed <= 0)
	{
		Speed = 0;
	}

	Map1Vec.y += Speed;
	Map2Vec.y += Speed;

	//scroll Screen
	if (Map1Vec.y >= 600.0f)
	{
		Map1Vec.y = Map2Vec.y - 600.0f;
	}
	else if (Map2Vec.y >= 600.0f)
	{
		Map2Vec.y = Map1Vec.y - 600.0f;
	}

}

void Update()
{
	switch (currentScreen)
	{
	case Intro:
		IntroUpdate();
		break;
	case Game1:
		GameUpdate();
		break;
	case Main:
		MainUpdate();
		break;
	}

	beforeClick = currentClick;
}

void IntroRender()
{
	if (g_pIntro.Visible == TRUE)
	{
		g_pSprite->Draw(g_pIntro.Tex, &ScreenRect, 0, &ScreenVec, 0xfffffffff);
	}
	else if (g_pIntro_off.Visible == TRUE)
	{
		g_pSprite->Draw(g_pIntro_off.Tex, &ScreenRect, 0, &ScreenVec, 0xfffffffff);
	}

	g_pSprite->Draw(g_pCloude1.Tex, &ScreenRect, 0, &g_pCloude1.Vec, 0xfffffffff);
	g_pSprite->Draw(g_pCloude2.Tex, &ScreenRect, 0, &g_pCloude2.Vec, 0xfffffffff);

	g_pSprite->Draw(g_pTitle.Tex, &g_pTitle.rc_Rect, 0, &g_pTitle.Vec, 0xfffffffff);
}

void GameRender()
{
	g_pSprite->Draw(g_pBack_For1.Tex, &ScreenRect, 0, &Map1Vec, 0xfffffffff);
	g_pSprite->Draw(g_pBack_For1.Tex, &ScreenRect, 0, &Map2Vec, 0xfffffffff);
	
	g_pSprite->Draw(g_pCar.Tex, &g_pCar.rc_Rect, 0, &g_pCar.Vec, 0xfffffffff);
	
	sprintf_s(SpeedStr, "%0.0f km/h\n", Speed * 10);
	sprintf_s(Name_spdStr, "SPEED\n");
	RECT SpeedNameRect{335, 10, 0, 0};
	RECT SpeedRect{300, 40, 0, 0 };

	Font->DrawTextA(g_pSprite, SpeedStr, -1, &SpeedRect, DT_NOCLIP, D3DCOLOR_XRGB(0, 180, 219));
	Font->DrawTextA(g_pSprite, Name_spdStr, -1, &SpeedNameRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 228, 0));

}

void MainRender()
{
	g_pSprite->Draw(g_pMain.Tex, &ScreenRect, 0, &ScreenVec, 0xfffffffff);

	if (g_pStart.Visible == TRUE)
	{
		g_pSprite->Draw(g_pStart.Tex, &ScreenRect, 0, &ScreenVec, 0xfffffffff);
	}
	else if (g_pExplan.Visible == TRUE)
	{
		g_pSprite->Draw(g_pExplan.Tex, &ScreenRect, 0, &ScreenVec, 0xfffffffff);
	}
	else if (g_pRank.Visible == TRUE)
	{
		g_pSprite->Draw(g_pRank.Tex, &ScreenRect, 0, &ScreenVec, 0xfffffffff);
	}
	else if (g_pExit.Visible == TRUE)
	{
		g_pSprite->Draw(g_pExit.Tex, &ScreenRect, 0, &ScreenVec, 0xfffffffff);
	}
	
	if (g_pExit_Yes.Visible == TRUE)
	{
		g_pSprite->Draw(g_pExit_Yes.Tex, &ScreenRect, 0, &ScreenVec, 0xfffffffff);
	}
	else if (g_pExit_No.Visible == TRUE)
	{
		g_pSprite->Draw(g_pExit_No.Tex, &ScreenRect, 0, &ScreenVec, 0xfffffffff);
	}
}

VOID Render()
{
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		switch (currentScreen)
		{
		case Intro:
			IntroRender();
			break;
		case Game1:
			GameRender();
			break;
		case Main:
			MainRender();
			break;
		}

		g_pSprite->End();
		g_pd3dDevice->EndScene();
	}
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			Cleanup();
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		currentClick = true;
		g_MouseX = LOWORD(lParam);
		g_MouseY = HIWORD(lParam);
		break;

	case WM_LBUTTONUP:
		currentClick = false;
		g_MouseX = LOWORD(lParam);
		g_MouseY = HIWORD(lParam);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	Initilize();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Render();
			Update();
		}
	}

	UnregisterClass("D3D Tutorial", g_wc.hInstance);
	return 0;
}