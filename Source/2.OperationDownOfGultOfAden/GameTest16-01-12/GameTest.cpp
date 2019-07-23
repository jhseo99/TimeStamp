#include <d3d9.h>
#include <d3dx9.h>
#include <stdlib.h>
#include <Windows.h>
#include <strsafe.h>
#include <time.h>
#include <math.h>
#pragma comment (lib, "winmm.lib")
#pragma warning(disable : 4996)

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
LPD3DXFONT Fonts = NULL;

LPD3DXSPRITE g_pSprite;
WNDCLASSEX g_wc;
HWND g_hWnd;

ID3DXFont *Font;

//Texture
LPDIRECT3DTEXTURE9 g_pBulletTex = NULL;
LPDIRECT3DTEXTURE9 g_pConTex = NULL;
LPDIRECT3DTEXTURE9 g_pGrenTex = NULL;
LPDIRECT3DTEXTURE9 g_pEBulletTex = NULL;
LPDIRECT3DTEXTURE9 g_pHeliTex = NULL;
LPDIRECT3DTEXTURE9 g_pClearTex = NULL;
LPDIRECT3DTEXTURE9 g_pEnemy_LTex = NULL;
LPDIRECT3DTEXTURE9 g_pEnemy_RTex = NULL;
LPDIRECT3DTEXTURE9 g_pHP_UPTex = NULL;
LPDIRECT3DTEXTURE9 g_pBack_s2_1 = NULL;

//Rect
RECT rc_Screen;
RECT rc_Bullet;
RECT rc_Container;
RECT rc_Gren;
RECT rc_Enem;
RECT rc_Heli;
RECT rc_Clear;
RECT rc_HPUP;
RECT rc_Boss;

//Mouse
bool beforeClick = false;
bool currentClick = false;
int g_MouseX = 0;
int g_MouseY = 0;

//Jump Sys
float Grav = -20.0f;;
float GrenGrav = -15.0f;
int speed = 4.5f;

//Respawn
float bullettime = 0.0f;
int Bulletcount = 0;
float Anitime = 0.0f;
float Grentime = 0.0f;
int GrenCount = 0;
float enemytime = 0.0f;
int enemyCount = 0;
float Helitime = 0.0f;
int HeliCount = 0;
float Itemtime = 0.0f;
int itemcount = 0;

//UI sys
int HP = 5;
int score = 0;
int Coin = 5;

//Font
char HPStr[10];
char ScoreStr[1000];
char CoinStr[10];

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT InitD3D(HWND hWnd);

//ScreenState
enum ScreenState
{
	INTRO,
	MENU,
	GAME1,
	GAME2,
	DIE,
	LOADING,
	END,
	ENDING,
};
ScreenState currentScreen = INTRO;
ScreenState beforeScreen;

//PlayerState
enum PlayerState
{
	STAND,
	RIGHT,
	LEFT,
	DOWN,
	UP,
	UPLEFT,
	UPRIGHT,
};
PlayerState currentPlayer = STAND;
PlayerState beforePlayer = RIGHT;

struct TEXTURE
{
	LPDIRECT3DTEXTURE9 Tex = NULL;
	D3DXVECTOR3 Vec;
	BOOL Visible;
	RECT rc;
};
TEXTURE g_pInt_Gun;
TEXTURE g_pTitle;
TEXTURE g_pBreak;
TEXTURE g_pBreak_2;
TEXTURE g_pMenu;
TEXTURE g_pStart;
TEXTURE g_pRank;
TEXTURE g_pHowto;
TEXTURE g_pExit;
TEXTURE g_pWin_start;
TEXTURE g_pWin_Exit;
TEXTURE g_pBacks1_1;
TEXTURE g_pBacks1_2;
TEXTURE g_pDie;
TEXTURE g_pBomb;
TEXTURE g_pEnding;

struct Player
{
	LPDIRECT3DTEXTURE9 Tex = NULL;
	D3DXVECTOR3 Vec;
	BOOL GROUND;
	BOOL DOWN;
	BOOL LEFT;
	BOOL RIGHT;
	BOOL HIT;
	BOOL LEFTRUN;
	BOOL RIGHTRUN;
	RECT rc;
	float Ani = 0.0f;
};
Player g_pPlayer;
Player g_pPlayerTex[6];

struct Button
{
	RECT rc;
};
Button Start;
Button Rank;
Button Howto;
Button Exit;
Button Yes;
Button No;

struct Arraytex
{
	BOOL Visible;
	D3DXVECTOR3 Vec;
	bool left;
	bool right;
	bool up;
	bool upleft;
	bool upright;
	bool down;
	bool downleft;
	bool downright;
};
Arraytex g_pBullet[100];
Arraytex g_pGrend[5];
Arraytex g_pContainer[3];
Arraytex g_pHP_UP[10];

struct Weapon
{
	float firetime = 0.0f;
	BOOL Visible;
	D3DXVECTOR3 Vec;
	bool left;
	bool right;
};

struct Enemy
{
	int Hp = 5;
	Weapon Bullet[10];
	int Bulletcount = 0;
	D3DXVECTOR3 Vec;
	BOOL Visible;
	BOOL GROUND;
	BOOL HIT;
	bool fire;
	bool left;
	bool right;
};
Enemy g_pEnemy[100];
Enemy g_pHeli[100];

void InitWin(void)
{
	WNDCLASSEX g_wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"D3D Tutorial", NULL };
	RegisterClassEx(&g_wc);

	g_hWnd = CreateWindow("D3D Tutorial", "Game",
		WS_OVERLAPPED, 0, 0, 800, 600,
		GetDesktopWindow(), NULL, g_wc.hInstance, NULL);
}

void InitDX(void)
{
	ShowCursor(TRUE);
	InitD3D(g_hWnd);
	D3DXCreateSprite(g_pd3dDevice, &g_pSprite);

	//Rect
	rc_Screen.right = 800;
	rc_Screen.bottom = 600;

	g_pInt_Gun.rc.right = 285;
	g_pInt_Gun.rc.bottom = 170;

	g_pTitle.rc.right = 403;
	g_pTitle.rc.bottom = 154;

	g_pWin_start.rc.right = 390;
	g_pWin_start.rc.bottom = 198;

	g_pWin_Exit.rc.right = 390;
	g_pWin_Exit.rc.bottom = 198;

	g_pPlayer.rc.right = 80;
	g_pPlayer.rc.bottom = 120;

	rc_Bullet.right = 40;
	rc_Bullet.bottom = 40;

	rc_Container.right = 250;
	rc_Container.bottom = 200;

	rc_Gren.right = 70;
	rc_Gren.bottom = 120;

	rc_Enem.right = 80;
	rc_Enem.bottom = 120;

	rc_Heli.right = 300;
	rc_Heli.bottom = 80;

	rc_Clear.right = 50;
	rc_Clear.bottom = 100;

	rc_HPUP.right = 60;
	rc_HPUP.bottom = 60;

	//button Rect
	Start.rc.left = 562;
	Start.rc.top = 156;
	Start.rc.right = 759;
	Start.rc.bottom = 220;

	Rank.rc.left = 562;
	Rank.rc.top = 236;
	Rank.rc.right = 759;
	Rank.rc.bottom = 301;

	Howto.rc.left = 562;
	Howto.rc.top = 315;
	Howto.rc.right = 759;
	Howto.rc.bottom = 379;

	Exit.rc.left = 562;
	Exit.rc.top = 396;
	Exit.rc.right = 759;
	Exit.rc.bottom = 453;

	Yes.rc.left = 226;
	Yes.rc.top = 277;
	Yes.rc.right = 363;
	Yes.rc.bottom = 342;

	No.rc.left = 400;
	No.rc.top = 277;
	No.rc.right = 537;
	No.rc.bottom = 342;

	g_pBomb.rc.right = 70;
	g_pBomb.rc.bottom = 120;

	rc_Boss.right = 256;
	rc_Boss.bottom = 256;

	//Vec
	g_pInt_Gun.Vec.x = 800.0f;
	g_pInt_Gun.Vec.y = 200.0f;

	g_pTitle.Vec.x = 250.0f;
	g_pTitle.Vec.y = 200.0f;

	g_pBreak.Vec.x = 0.0f;
	g_pBreak.Vec.y = 0.0f;

	g_pMenu.Vec.x = 0.0f;
	g_pMenu.Vec.y = 0.0f;

	g_pStart.Vec.x = 0.0f;
	g_pStart.Vec.y = 0.0f;

	g_pRank.Vec.x = 0.0f;
	g_pRank.Vec.y = 0.0f;

	g_pHowto.Vec.x = 0.0f;
	g_pHowto.Vec.y = 0.0f;

	g_pExit.Vec.x = 0.0f;
	g_pExit.Vec.y = 0.0f;

	g_pWin_start.Vec.x = 187.0f;
	g_pWin_start.Vec.y = 197.0f;

	g_pWin_Exit.Vec.x = 187.0f;
	g_pWin_Exit.Vec.y = 197.0f;

	g_pBacks1_1.Vec.x = 0.0f;
	g_pBacks1_1.Vec.y = 0.0f;

	g_pBacks1_2.Vec.x = 800.0f;
	g_pBacks1_2.Vec.y = 0.0f;

	g_pDie.Vec.x = 0.0f;
	g_pDie.Vec.y = 0.0f;

	g_pPlayer.Vec.x = 150.0f;
	g_pPlayer.Vec.y = 400.0f;

	g_pContainer[0].Vec.x = 400.0f;
	g_pContainer[0].Vec.y = 350.0f;

	g_pContainer[1].Vec.x = 950.0f;
	g_pContainer[1].Vec.y = 350.0f;

	g_pContainer[2].Vec.x = 1300.0f;
	g_pContainer[2].Vec.y = 350.0f;

	g_pEnding.Vec.x = 0.0f;
	g_pEnding.Vec.y = 0.0f;

	D3DXCreateFont(g_pd3dDevice, 30, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "奔覆眉", &Font);
}

void LoadData(void)
{
	D3DXCreateTextureFromFile(g_pd3dDevice, "intGun.png", &g_pInt_Gun.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Title.png", &g_pTitle.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Break.png", &g_pBreak.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Break2.png", &g_pBreak_2.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Menu.png", &g_pMenu.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Start.png", &g_pStart.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Rank.png", &g_pRank.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Howto.png", &g_pHowto.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Exit.png", &g_pExit.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Start_win.png", &g_pWin_start.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Exit_Win.png", &g_pWin_Exit.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Backs1_1.png", &g_pBacks1_1.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Backs1_2.png", &g_pBacks1_2.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Player_L.png", &g_pPlayerTex[0].Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Player_R.png", &g_pPlayerTex[1].Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Player_LU.png", &g_pPlayerTex[2].Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Player_RU.png", &g_pPlayerTex[3].Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Player_LD.png", &g_pPlayerTex[4].Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Player_RD.png", &g_pPlayerTex[5].Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Bullet.png", &g_pBulletTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Container.png", &g_pConTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Grenade.png", &g_pGrenTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Enemy_L.png", &g_pEnemy_LTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Enemy_R.png", &g_pEnemy_RTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "EBullet.png", &g_pEBulletTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Heli.png", &g_pHeliTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Clear.png", &g_pClearTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Die.png", &g_pDie.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Bomb.png", &g_pBomb.Tex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "HP_UP.png", &g_pHP_UPTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Backs2_1.png", &g_pBack_s2_1);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Ending.png", &g_pEnding.Tex);
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

VOID CleanUp()
{
	if (g_pSprite != NULL)
		g_pSprite->Release();
	if (g_pD3D != NULL)
		g_pD3D->Release();
	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();
}

void Initilize(void)
{
	InitWin();
	InitDX();
	LoadData();

	ShowWindow(g_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(g_hWnd);
}

void IntroUpdate()
{
	if (beforeClick == false && currentClick == true)
	{
		g_pInt_Gun.Visible = TRUE;
	}
	if (g_pInt_Gun.Visible == TRUE)
	{
		g_pInt_Gun.Vec.x -= 7.0f;
		if (g_pInt_Gun.Vec.x < 515.0f)
		{
			g_pInt_Gun.Vec.x += 7.0f;
			g_pTitle.Visible = TRUE;
		}
	}
	if (g_pTitle.Visible == TRUE)
	{
		g_pTitle.Vec.x -= 8.0f;
		if (g_pTitle.Vec.x < 20)
		{
			g_pTitle.Vec.x += 8.0f;
			Anitime += 0.5f;
			if (Anitime < 10)
			{
				g_pBreak.Visible = TRUE;
				g_pBreak_2.Visible = FALSE;
			}
			else if (Anitime > 10)
			{
				g_pBreak.Visible = FALSE;
				g_pBreak_2.Visible = TRUE;

				if (Anitime > 20)
				{
					Anitime = 0.0f;
				}
			}
		}
	}


	if (g_pBreak.Visible == TRUE || g_pBreak_2.Visible == TRUE)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			currentScreen = MENU;
		}
	}
}

void MenuUpdate()
{
	POINT pos;
	GetCursorPos(&pos);
	
	if (pos.x > Start.rc.left && pos.x < Start.rc.right &&
		pos.y > Start.rc.top && pos.y < Start.rc.bottom)
	{
		if (beforeClick == false && currentClick == true)
		{
			g_pWin_start.Visible = TRUE;
		}

		g_pStart.Visible = TRUE;
		g_pRank.Visible = FALSE;
		g_pHowto.Visible = FALSE;
		g_pExit.Visible = FALSE;
		g_pMenu.Visible = FALSE;
	}
	else if (pos.x > Rank.rc.left && pos.x < Rank.rc.right &&
		pos.y > Rank.rc.top && pos.y < Rank.rc.bottom)
	{
		g_pStart.Visible = FALSE;
		g_pRank.Visible = TRUE;
		g_pHowto.Visible = FALSE;
		g_pExit.Visible = FALSE;
		g_pMenu.Visible = FALSE;
	}
	else if (pos.x > Howto.rc.left && pos.x < Howto.rc.right &&
		pos.y > Howto.rc.top && pos.y < Howto.rc.bottom)
	{
		g_pStart.Visible = FALSE;
		g_pRank.Visible = FALSE;
		g_pHowto.Visible = TRUE;
		g_pExit.Visible = FALSE;
		g_pMenu.Visible = FALSE;
	}
	else if (pos.x > Exit.rc.left && pos.x < Exit.rc.right &&
		pos.y > Exit.rc.top && pos.y < Exit.rc.bottom)
	{
		if (beforeClick == false && currentClick == true)
		{
			g_pWin_Exit.Visible = TRUE;
		}
		
		g_pStart.Visible = FALSE;
		g_pRank.Visible = FALSE;
		g_pHowto.Visible = FALSE;
		g_pExit.Visible = TRUE;
		g_pMenu.Visible = FALSE;
	}
	else
	{
		g_pStart.Visible = FALSE;
		g_pRank.Visible = FALSE;
		g_pHowto.Visible = FALSE;
		g_pExit.Visible = FALSE;
		g_pMenu.Visible = TRUE;
	}

	if (g_pWin_start.Visible == TRUE)
	{
		if (beforeClick == false && currentClick == true)
		{
			if (g_MouseX > Yes.rc.left && g_MouseX < Yes.rc.right &&
				g_MouseY > Yes.rc.top && g_MouseY < Yes.rc.bottom)
			{
				currentScreen = GAME1;
			}
			else if (g_MouseX > No.rc.left && g_MouseX < No.rc.right &&
				g_MouseY > No.rc.top && g_MouseY < No.rc.bottom)
			{
				g_pWin_start.Visible = FALSE;
				currentScreen = MENU;
			}
		}
	}
	if (g_pWin_Exit.Visible == TRUE)
	{
		if (beforeClick == false && currentClick == true)
		{
			if (g_MouseX > Yes.rc.left && g_MouseX < Yes.rc.right &&
				g_MouseY > Yes.rc.top && g_MouseY < Yes.rc.bottom)
			{
				CleanUp();
				PostQuitMessage(0);
			}
			else if (g_MouseX > No.rc.left && g_MouseX < No.rc.right &&
				g_MouseY > No.rc.top && g_MouseY < No.rc.bottom)
			{
				g_pWin_Exit.Visible = FALSE;
				currentScreen = MENU;
			}
		}
	}
}

void Game1Update()
{
	beforeScreen = currentScreen;

	//player Move
	if (GetAsyncKeyState(VK_LEFT))
	{
		g_pPlayer.Vec.x -= speed;
		
		g_pPlayer.RIGHT = FALSE;
		g_pPlayer.LEFT = TRUE;

		beforePlayer = LEFT;
		if (GetAsyncKeyState('S'))
		{
			g_pPlayer.LEFT = FALSE;
			currentPlayer = UPLEFT;
			beforePlayer = currentPlayer;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		g_pPlayer.Vec.x += speed;

		g_pPlayer.LEFT = FALSE;
		g_pPlayer.RIGHT = TRUE;

		beforePlayer = RIGHT;
		if (GetAsyncKeyState('S'))
		{
			g_pPlayer.RIGHT = FALSE;
			currentPlayer = UPRIGHT;
			beforePlayer = currentPlayer;
		}
	}
	else if (GetAsyncKeyState('S'))
	{
		currentPlayer = UP;
		if (GetAsyncKeyState(VK_LEFT))
		{
			currentPlayer = UPLEFT;
			beforePlayer = currentPlayer;
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			currentPlayer = UPRIGHT;
			beforePlayer = currentPlayer;
		}
	}

	//Jump sys
	if (currentPlayer == UP)
	{	
		g_pPlayer.Vec.y += Grav;
		Grav += 0.8;
	}
	else if (currentPlayer == UPLEFT)
	{
		g_pPlayer.Vec.y += Grav;
		Grav += 0.8;

		g_pPlayer.Vec.x -= 0.01f;
	}
	else if (currentPlayer == UPRIGHT)
	{
		g_pPlayer.Vec.y += Grav;
		Grav += 0.8;

		g_pPlayer.Vec.x += 0.01f;
	}
	else if (g_pPlayer.DOWN == TRUE)
	{
		Grav = 15.0f;
		g_pPlayer.Vec.y += Grav;

		Grav += 0.8;
	}

	if (g_pPlayer.GROUND == TRUE)
	{	
		if (g_pPlayer.Vec.y >= 240.0f)
		{
			g_pPlayer.GROUND = FALSE;

			g_pPlayer.Vec.y = 240.0f;
			currentPlayer = STAND;

			Grav = -20.0f;
		}
	}

	if (g_pPlayer.Vec.y > 400.0f)
	{
		g_pPlayer.Vec.y = 400.0f;
		currentPlayer = STAND;

		Grav = -20.0f;
	}

	//Hit Ani
	if (g_pPlayer.HIT == TRUE)
	{
		Anitime += 1.0f;
		if (Anitime > 10)
		{
			g_pPlayer.HIT = FALSE;
			Anitime = 0.0f;
		}
	}
	//=================================================

	//container

	for (int i = 0; i < 3; i++)
	{
		if (g_pPlayer.Vec.x > g_pContainer[i].Vec.x + 235 ||
			g_pPlayer.Vec.x + 65 < g_pContainer[i].Vec.x ||
			g_pPlayer.Vec.y > g_pContainer[i].Vec.y + 200 ||
			g_pPlayer.Vec.y + 120 < g_pContainer[i].Vec.y)
		{

		}
		else
		{
			if (g_pPlayer.Vec.x < g_pContainer[i].Vec.x + 200 ||
				g_pPlayer.Vec.x + 30 > g_pContainer[i].Vec.x)
			{
				if (g_pPlayer.Vec.y + 90 <= g_pContainer[i].Vec.y)
				{
					g_pPlayer.GROUND = TRUE;
				}
			}
		}

		if (g_pPlayer.GROUND == TRUE)
		{
			if (g_pPlayer.Vec.x + 30 <= g_pContainer[i].Vec.x ||
				g_pPlayer.Vec.x >= g_pContainer[i].Vec.x + 200)
			{
				g_pPlayer.DOWN = TRUE;
			}
		}
	}

	//=================================================


	//Screen Scroll & Limit line
	if (g_pPlayer.Vec.x + g_pPlayer.rc.bottom > 700.0f)
	{
		g_pPlayer.Vec.x = 700 - g_pPlayer.rc.bottom;
		
		g_pBacks1_1.Vec.x -= 4.5f;
		g_pBacks1_2.Vec.x -= 4.5f;

		g_pContainer[0].Vec.x -= 4.5f;
		g_pContainer[1].Vec.x -= 4.5f;
		g_pContainer[2].Vec.x -= 4.5f;

		for (int i = 0; i < 100; i++)
		{
			if (g_pEnemy[i].Visible == TRUE)
			{
				g_pEnemy[i].Vec.x -= 4.5f;
				for (int j = 0; j < 10; j++)
				{
					g_pEnemy[i].Bullet[j].Vec.x -= 4.5f;
				}
			}
		}

		for (int i = 0; i < 100; i++)
		{
			if (g_pBullet[i].Visible == TRUE)
			{
				g_pBullet[i].Vec.x -= 4.5f;
			}
		}

		for (int i = 0; i < 100; i++)
		{
			if (g_pHeli[i].Visible == TRUE)
			{
				g_pHeli[i].Vec.x -= 4.5f;
				for (int j = 0; j < 10; j++)
				{
					g_pHeli[i].Bullet[j].Vec.x -= 4.5f;
				}
			}
		}

		for (int i = 0; i < 10; i++)
		{
			if (g_pHP_UP[i].Visible == TRUE)
			{
				g_pHP_UP[i].Vec.x -= 4.5f;
			}
		}

		if (g_pBacks1_1.Vec.x < -800)
		{
			g_pBacks1_1.Vec.x += 4.5f;
			g_pBacks1_2.Vec.x += 4.5f;

			g_pContainer[0].Vec.x += 4.5f;
			g_pContainer[1].Vec.x += 4.5f;
			g_pContainer[2].Vec.x += 4.5f;

			for (int i = 0; i < 100; i++)
			{
				if (g_pEnemy[i].Visible == TRUE)
				{
					g_pEnemy[i].Vec.x += 4.5f;
					for (int j = 0; j < 10; j++)
					{
						g_pEnemy[i].Bullet[j].Vec.x += 4.5f;
					}
				}
			}

			for (int i = 0; i < 100; i++)
			{
				if (g_pBullet[i].Visible == TRUE)
				{
					g_pBullet[i].Vec.x += 4.5f;
				}
			}

			for (int i = 0; i < 100; i++)
			{
				if (g_pHeli[i].Visible == TRUE)
				{
					g_pHeli[i].Vec.x += 4.5f;
					for (int j = 0; j < 10; j++)
					{
						g_pHeli[i].Bullet[j].Vec.x += 4.5f;
					}
				}
			}

			for (int i = 0; i < 10; i++)
			{
				if (g_pHP_UP[i].Visible == TRUE)
				{
					g_pHP_UP[i].Vec.x += 4.5f;
				}
			}
		}
	}
	else if (g_pPlayer.Vec.x < 70.0f)
	{
		g_pPlayer.Vec.x = 70.0f;
		
		g_pBacks1_1.Vec.x += 4.5f;
		g_pBacks1_2.Vec.x += 4.5f;

		g_pContainer[0].Vec.x += 4.5f;
		g_pContainer[1].Vec.x += 4.5f;
		g_pContainer[2].Vec.x += 4.5f;

		for (int i = 0; i < 100; i++)
		{
			if (g_pEnemy[i].Visible == TRUE)
			{
				g_pEnemy[i].Vec.x += 4.5f;
				for (int j = 0; j < 10; j++)
				{
					g_pEnemy[i].Bullet[j].Vec.x += 4.5f;
				}
			}
		}

		for (int i = 0; i < 100; i++)
		{
			if (g_pBullet[i].Visible == TRUE)
			{
				g_pBullet[i].Vec.x += 4.5f;
			}
		}

		for (int i = 0; i < 100; i++)
		{
			if (g_pHeli[i].Visible == TRUE)
			{
				g_pHeli[i].Vec.x += 4.5f;
				for (int j = 0; j < 10; j++)
				{
					g_pHeli[i].Bullet[j].Vec.x += 4.5f;
				}
			}
		}

		for (int i = 0; i < 10; i++)
		{
			if (g_pHP_UP[i].Visible == TRUE)
			{
				g_pHP_UP[i].Vec.x += 4.5f;
			}
		}

		if (g_pBacks1_1.Vec.x > 0)
		{
			g_pBacks1_1.Vec.x -= 4.5f;
			g_pBacks1_2.Vec.x -= 4.5f;

			g_pContainer[0].Vec.x -= 4.5f;
			g_pContainer[1].Vec.x -= 4.5f;
			g_pContainer[2].Vec.x -= 4.5f;

			for (int i = 0; i < 100; i++)
			{
				if (g_pEnemy[i].Visible == TRUE)
				{
					g_pEnemy[i].Vec.x -= 4.5f;
					for (int j = 0; j < 10; j++)
					{
						g_pEnemy[i].Bullet[j].Vec.x -= 4.5f;
					}
				}
			}

			for (int i = 0; i < 100; i++)
			{
				if (g_pBullet[i].Visible == TRUE)
				{
					g_pBullet[i].Vec.x -= 4.5f;
				}
			}

			for (int i = 0; i < 100; i++)
			{
				if (g_pHeli[i].Visible == TRUE)
				{
					g_pHeli[i].Vec.x -= 4.5f;
					for (int j = 0; j < 10; j++)
					{
						g_pHeli[i].Bullet[j].Vec.x -= 4.5f;
					}
				}
			}

			for (int i = 0; i < 10; i++)
			{
				if (g_pHP_UP[i].Visible == TRUE)
				{
					g_pHP_UP[i].Vec.x -= 4.5f;
				}
			}
		}
	}

	//======================================================

	//GunFire
	if (GetAsyncKeyState('A'))
	{
		bullettime += 1.0f;

		if (bullettime > 10)
		{
			g_pBullet[Bulletcount].Visible = TRUE;

			g_pBullet[Bulletcount].Vec.y = -120.0f;

			if (GetAsyncKeyState(VK_LEFT))
			{
				g_pBullet[Bulletcount].Vec.x = g_pPlayer.Vec.x;
				g_pBullet[Bulletcount].Vec.y = g_pPlayer.Vec.y + 70;

				if (GetAsyncKeyState(VK_UP))
				{
					g_pBullet[Bulletcount].upleft = true;
				}
				else if (GetAsyncKeyState(VK_DOWN))
				{
					g_pBullet[Bulletcount].downleft = true;
				}
				else
				{
					g_pBullet[Bulletcount].left = true;
				}
			}
			else if (GetAsyncKeyState(VK_RIGHT))
			{
				g_pBullet[Bulletcount].Vec.x = g_pPlayer.Vec.x + 70;
				g_pBullet[Bulletcount].Vec.y = g_pPlayer.Vec.y + 70;

				if (GetAsyncKeyState(VK_UP))
				{
					g_pBullet[Bulletcount].upright = true;
				}
				else if (GetAsyncKeyState(VK_DOWN))
				{
					g_pBullet[Bulletcount].downright = true;
				}
				else
				{
					g_pBullet[Bulletcount].right = true;
				}
			}
			else if (GetAsyncKeyState(VK_UP))
			{
				g_pBullet[Bulletcount].Vec.x = g_pPlayer.Vec.x + 40;
				g_pBullet[Bulletcount].Vec.y = g_pPlayer.Vec.y + 70;

				if (GetAsyncKeyState(VK_LEFT))
				{
					g_pBullet[Bulletcount].upleft = true;
				}
				else if (GetAsyncKeyState(VK_RIGHT))
				{
					g_pBullet[Bulletcount].upright = true;
				}
				else
				{
					g_pBullet[Bulletcount].up = true;
				}
			}
			else if (GetAsyncKeyState(VK_DOWN))
			{
				g_pBullet[Bulletcount].Vec.x = g_pPlayer.Vec.x + 40;
				g_pBullet[Bulletcount].Vec.y = g_pPlayer.Vec.y + 70;

				if (GetAsyncKeyState(VK_LEFT))
				{
					g_pBullet[Bulletcount].downleft = true;
				}
				else if (GetAsyncKeyState(VK_RIGHT))
				{
					g_pBullet[Bulletcount].downright = true;
				}
				else
				{
					g_pBullet[Bulletcount].down = true;
				}
			}

			if (Bulletcount >= 99)
			{
				Bulletcount = 0;
			}

			bullettime = 0.0f;
			Bulletcount++;
		}
	}
	//==================================================

	//GunMove
	for (int i = 0; i < 100; i++)
	{
		if (g_pBullet[i].Visible == TRUE)
		{
			if (g_pBullet[i].left == true)
			{
				g_pBullet[i].Vec.x -= 10.0f;
			}
			else if (g_pBullet[i].right == true)
			{
				g_pBullet[i].Vec.x += 10.0f;
			}
			else if (g_pBullet[i].up == true)
			{
				g_pBullet[i].Vec.y -= 10.0f;
			}
			else if (g_pBullet[i].upleft == true)
			{
				g_pBullet[i].Vec.x -= 7.1f;
				g_pBullet[i].Vec.y -= 7.1f;
			}
			else if (g_pBullet[i].upright == true)
			{
				g_pBullet[i].Vec.x += 7.1f;
				g_pBullet[i].Vec.y -= 7.1f;
			}
			else if (g_pBullet[i].down == true)
			{
				g_pBullet[i].Vec.y += 10.0f;
			}
			else if (g_pBullet[i].downleft == true)
			{
				g_pBullet[i].Vec.x -= 7.1f;
				g_pBullet[i].Vec.y += 7.1f;
			}
			else if (g_pBullet[i].downright == true)
			{
				g_pBullet[i].Vec.x += 7.1f;
				g_pBullet[i].Vec.y += 7.1f;
			}

			if (g_pBullet[i].Vec.x > 800 || g_pBullet[i].Vec.x < -760 ||
				g_pBullet[i].Vec.y < -25)
			{
				g_pBullet[i].Visible = FALSE;
			}
		}
		else if (g_pBullet[i].Visible == FALSE)
		{
			g_pBullet[i].left = false;
			g_pBullet[i].right = false;
			g_pBullet[i].up = false;
			g_pBullet[i].upleft = false;
			g_pBullet[i].upright = false;
			g_pBullet[i].down = false;
			g_pBullet[i].downleft = false;
			g_pBullet[i].downright = false;
		}
	}
	//==============================================================

	//GrenFire
	if (GetAsyncKeyState('D'))
	{
		Grentime += 1.0f;

		if (Grentime > 25 && GrenCount < 5 && g_pGrend[GrenCount-1].Visible == FALSE)
		{
			g_pGrend[GrenCount].Visible = TRUE;

			g_pGrend[GrenCount].Vec.x = g_pPlayer.Vec.x + 35;
			g_pGrend[GrenCount].Vec.y = g_pPlayer.Vec.y + 25;

			if (g_pPlayer.RIGHT == TRUE || g_pPlayer.RIGHTRUN == TRUE || currentPlayer == UPRIGHT)
			{
				g_pGrend[GrenCount].right = true;
			}
			else if (g_pPlayer.LEFT == TRUE || g_pPlayer.LEFTRUN == TRUE || currentPlayer == UPLEFT)
			{
				g_pGrend[GrenCount].left = true;
			}
			else if (currentPlayer == UP)
			{
				g_pGrend[GrenCount].down = true;
			}
			else
			{
				g_pGrend[GrenCount].Visible = FALSE;
			}

			Grentime = 0.0f;
			GrenCount++;
		}
	}
	//===================================================

	//GrenMove
	for (int i = 0; i < 5; i++)
	{
		if (g_pGrend[i].Visible == TRUE)
		{	
			if (g_pGrend[i].left == true)
			{
				g_pGrend[i].Vec.y += GrenGrav;
				GrenGrav += 1.0f;

				g_pGrend[i].Vec.x -= 5.0f;
			}
			else if (g_pGrend[i].right == true)
			{
				g_pGrend[i].Vec.y += GrenGrav;
				GrenGrav += 1.0f;

				g_pGrend[i].Vec.x += 5.0f;
			}
			else if (g_pGrend[i].down == true)
			{
				g_pGrend[i].Vec.y += GrenGrav;
				GrenGrav += 1.0f;
			}

			if (g_pGrend[i].Vec.y > 550)
			{
				GrenGrav = -15.0f;
				g_pGrend[i].Visible = FALSE;
			}
		}
		else if (g_pGrend[i].Visible == FALSE)
		{
			g_pGrend[i].left = false;
			g_pGrend[i].right = false;
		}
	}
	//=========================================================

	//Enemy sys

	//Respawn
	enemytime += 1.0f;
	if (enemytime > 200)
	{
		g_pEnemy[enemyCount].Visible = TRUE;

		g_pEnemy[enemyCount].Vec.x = (float)(rand() % 700 + 100);
		g_pEnemy[enemyCount].Vec.y = -120.0f;

		if (g_pEnemy[enemyCount].Vec.x < g_pPlayer.Vec.x)
		{
			g_pEnemy[enemyCount].right = true;
			g_pEnemy[enemyCount].left = false;
		}
		else if (g_pEnemy[enemyCount].Vec.x >= g_pPlayer.Vec.x)
		{
			g_pEnemy[enemyCount].left = true;
			g_pEnemy[enemyCount].right = false;
		}

		if (enemyCount >= 99)
		{
			enemyCount = 0;
		}

		enemytime = 0.0f;
		enemyCount++;
	}

	if (score > 400)
	{
		//Respawn
		Helitime += 1.0f;
		if (score > 500)
		{
			Helitime += 1.0f;
		}

		if (Helitime > 300)
		{
			Helitime = 0.0f;
			
			g_pHeli[HeliCount].Visible = TRUE;

			g_pHeli[HeliCount].Vec.x = 800.0f;
			g_pHeli[HeliCount].Vec.y = 0.0f;

			if (HeliCount >= 99)
			{
				HeliCount = 0;
			}

			HeliCount++;
		}
	}
	//===================================================

	//Ground & Attack Respawn
	for (int i = 0; i < 100; i++)
	{
		if (g_pEnemy[i].Visible == TRUE)
		{
			g_pEnemy[i].Vec.y += 6.5f;
			
			if (g_pEnemy[i].Vec.y > 400)
			{
				g_pEnemy[i].Vec.y = 400.0f;
				g_pEnemy[i].GROUND = TRUE;
			}
		}
		if (g_pEnemy[i].GROUND == TRUE)
		{
			g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].firetime += 0.5f;

			if (g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].firetime > 30)
			{
				g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].firetime = 0.0f;
				g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].Visible = TRUE;

				g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].Vec.x = g_pEnemy[i].Vec.x + 20;
				g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].Vec.y = g_pEnemy[i].Vec.y + 50;

				if (g_pEnemy[i].left == true)
				{
					g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].left = true;
				}
				else if (g_pEnemy[i].right == true)
				{
					g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].right = true;
				}

				if (g_pEnemy[i].Bulletcount >= 9)
				{
					g_pEnemy[i].Bulletcount = 0;
				}

				g_pEnemy[i].Bulletcount++;
			}
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (g_pHeli[i].Visible == TRUE)
		{
			g_pHeli[i].Bullet[g_pHeli[i].Bulletcount].firetime += 0.5f;

			if (g_pHeli[i].Bullet[g_pHeli[i].Bulletcount].firetime > 10)
			{
				g_pHeli[i].Bullet[g_pHeli[i].Bulletcount].firetime = 0.0f;
				g_pHeli[i].Bullet[g_pHeli[i].Bulletcount].Visible = TRUE;

				g_pHeli[i].Bullet[g_pHeli[i].Bulletcount].Vec.x = g_pHeli[i].Vec.x;
				g_pHeli[i].Bullet[g_pHeli[i].Bulletcount].Vec.y = 0.0f;

				if (g_pHeli[i].Bulletcount >= 9)
				{
					g_pHeli[i].Bulletcount = 0;
				}

				g_pHeli[i].Bulletcount++;
			}
		}
	}
	//==================================================

	//AttackMove
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (g_pEnemy[i].Bullet[j].Visible == TRUE)
			{	
				if (g_pEnemy[i].Bullet[j].left == true)
				{
					g_pEnemy[i].Bullet[j].Vec.x -= 5.0f;
				}
				else if (g_pEnemy[i].Bullet[j].right == true)
				{
					g_pEnemy[i].Bullet[j].Vec.x += 5.0f;
				}
			}
			else
			{
				g_pEnemy[i].Bullet[j].left = false;
				g_pEnemy[i].Bullet[j].right = false;
			}
		}

		if (g_pEnemy[i].Visible == FALSE)
		{
			g_pEnemy[i].GROUND = FALSE;
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (g_pHeli[i].Visible == TRUE)
		{
			g_pHeli[i].Vec.x -= 7.0f;

			for (int j = 0; j < 10; j++)
			{
				if (g_pHeli[i].Bullet[j].Visible == TRUE)
				{
					g_pHeli[i].Bullet[j].Vec.y += 6.5f;
				}
			}
		}
	}

	//=====================================================

	//item
	if (HP < 3)
	{
		Itemtime += 1.0f;
		if (Itemtime > 100)
		{
			g_pHP_UP[itemcount].Visible = TRUE;

			g_pHP_UP[itemcount].Vec.x = (float)(rand() % 700 + 100);
			g_pHP_UP[itemcount].Vec.y = 0.0f;

			if (itemcount >= 9)
			{
				itemcount = 0;
			}

			Itemtime = 0.0f;
			itemcount++;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (g_pHP_UP[i].Visible == TRUE)
		{
			g_pHP_UP[i].Vec.y += 4.0f;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (g_pHP_UP[i].Visible == TRUE)
		{
			if (g_pPlayer.Vec.x + 10 > g_pHP_UP[i].Vec.x + rc_HPUP.bottom ||
				g_pPlayer.Vec.x + g_pPlayer.rc.bottom - 10 < g_pHP_UP[i].Vec.x ||
				g_pPlayer.Vec.y > g_pHP_UP[i].Vec.y + rc_HPUP.right ||
				g_pPlayer.Vec.y + g_pPlayer.rc.right < g_pHP_UP[i].Vec.y)
			{

			}
			else
			{
				g_pHP_UP[i].Visible = FALSE;
				HP++;
			}
		}
	}
	//==============================================================

	//面倒贸府
	for (int i = 0; i < 100; i++)
	{
		if (g_pEnemy[i].Visible == TRUE)
		{
			for (int check = 0; check < 100; check++)
			{
				if (g_pBullet[check].Visible == TRUE && g_pEnemy[i].GROUND == TRUE)
				{
					if (g_pBullet[check].Vec.x > g_pEnemy[i].Vec.x + rc_Enem.bottom ||
						g_pBullet[check].Vec.x + rc_Bullet.bottom < g_pEnemy[i].Vec.x ||
						g_pBullet[check].Vec.y > g_pEnemy[i].Vec.y + rc_Enem.right ||
						g_pBullet[check].Vec.y + rc_Bullet.right < g_pEnemy[i].Vec.y)
					{

					}
					else
					{
						if (g_pEnemy[i].Hp <= 0)
						{
							g_pEnemy[i].Visible = FALSE;
						}
						g_pBullet[check].Visible = FALSE;
						g_pEnemy[i].Hp -= 2;
						score += 10;
					}
				}
			}
			
			for (int check = 0; check < 10; check++)
			{
				if (g_pGrend[check].Visible == TRUE && g_pEnemy[i].GROUND == TRUE)
				{
					if (g_pGrend[check].Vec.x > g_pEnemy[i].Vec.x + rc_Enem.bottom ||
						g_pGrend[check].Vec.x + rc_Gren.bottom < g_pEnemy[i].Vec.x ||
						g_pGrend[check].Vec.y > g_pEnemy[i].Vec.y + rc_Enem.right ||
						g_pGrend[check].Vec.y + rc_Gren.right < g_pEnemy[i].Vec.y)
					{

					}
					else
					{
						if (g_pEnemy[i].Hp <= 0)
						{
							g_pEnemy[i].Visible = FALSE;
						}
						g_pGrend[check].Visible = FALSE;
						g_pPlayer.HIT = TRUE;
						g_pBomb.Vec.x = g_pEnemy[i].Vec.x;
						g_pBomb.Vec.y = g_pEnemy[i].Vec.y;
						g_pEnemy[i].Hp -= 100;
						score += 30;
					}
				}
			}

			for (int j = 0; j < 10; j++)
			{
				if (g_pEnemy[i].Bullet[j].Visible == TRUE)
				{
					if (g_pPlayer.Vec.x + 10 > g_pEnemy[i].Bullet[j].Vec.x + rc_Bullet.bottom ||
						g_pPlayer.Vec.x + g_pPlayer.rc.bottom - 10 < g_pEnemy[i].Bullet[j].Vec.x ||
						g_pPlayer.Vec.y > g_pEnemy[i].Bullet[j].Vec.y + rc_Bullet.right ||
						g_pPlayer.Vec.y + g_pPlayer.rc.right < g_pEnemy[i].Bullet[j].Vec.y)
					{

					}
					else
					{
						g_pEnemy[i].Bullet[j].Visible = FALSE;
						HP--;
					}
				}
			}
		}
		if (g_pHeli[i].Visible == TRUE)
		{
			for (int j = 0; j < 10; j++)
			{
				if (g_pHeli[i].Bullet[j].Visible == TRUE)
				{
					if (g_pPlayer.Vec.x + 40 > g_pHeli[i].Bullet[j].Vec.x + rc_Clear.bottom ||
						g_pPlayer.Vec.x + g_pPlayer.rc.bottom - 40 < g_pHeli[i].Bullet[j].Vec.x ||
						g_pPlayer.Vec.y + 50 > g_pHeli[i].Bullet[j].Vec.y + rc_Clear.right ||
						g_pPlayer.Vec.y + g_pPlayer.rc.right - 50 < g_pHeli[i].Bullet[j].Vec.y)
					{

					}
					else
					{
						g_pHeli[i].Bullet[j].Visible = FALSE;
						HP--;
						g_pPlayer.HIT = TRUE;
						g_pBomb.Vec.x = g_pHeli[i].Bullet[j].Vec.x;
						g_pBomb.Vec.y = g_pPlayer.Vec.y;
					}
				}
			}
		}
	}

	if (HP <= 0)
	{
		currentScreen = DIE;
	}

	if (score >= 700)
	{
		currentScreen = LOADING;
	}
}

void DieUpdate()
{
	if (Coin <= 0)
	{
		currentScreen = ENDING;
	}


	if (GetAsyncKeyState('R'))
	{
		if (Coin > 0)
		{
			Coin--;
			HP = 5;

			if (beforeScreen = GAME1)
			{
				currentScreen = GAME1;
			}
			if (beforeScreen = GAME2)
			{
				currentScreen = GAME2;
			}
		}
		else
		{
			currentScreen = DIE;
		}
	}
	else if (GetAsyncKeyState(VK_RETURN))
	{
		HP = 5;
		score = 0;
		GrenCount = 0;
		Coin = 5;

		g_pPlayer.Vec.x = 150.0f;
		g_pPlayer.Vec.y = 400.0f;

		g_pBomb.Visible = FALSE;

		g_pWin_start.Visible = FALSE;

		for (int i = 0; i < 5; i++)
		{
			g_pGrend[i].Visible = FALSE;
		}

		for (int i = 0; i < 100; i++)
		{
			g_pBullet[i].Visible = FALSE;

			g_pEnemy[i].Visible = FALSE;
			g_pHeli[i].Visible = FALSE;
		}

		for (int i = 0; i < 10; i++)
		{
			g_pHP_UP[i].Visible = FALSE;
		}

		currentScreen = MENU;
	}
}

void LoadingUpdate()
{
	g_pPlayer.Vec.x = 150.0f;
	g_pPlayer.Vec.y = 400.0f;

	g_pBomb.Visible = FALSE;

	for (int i = 0; i < 5; i++)
	{
		g_pGrend[i].Visible = FALSE;
	}

	for (int i = 0; i < 100; i++)
	{
		g_pBullet[i].Visible = FALSE;

		g_pEnemy[i].Visible = FALSE;
		g_pHeli[i].Visible = FALSE;
		for (int j = 0; j < 10; j++)
		{
			g_pEnemy[i].Bullet[j].Visible = FALSE;
			g_pHeli[i].Bullet[j].Visible = FALSE;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		g_pHP_UP[i].Visible = FALSE;
	}

	if (GetAsyncKeyState(VK_RETURN))
	{
		currentScreen = GAME2;
	}
}

void Game2Update()
{
	beforeScreen = currentScreen;

	//player Move
	if (GetAsyncKeyState(VK_LEFT))
	{
		g_pPlayer.Vec.x -= speed;

		g_pPlayer.RIGHT = FALSE;
		g_pPlayer.LEFT = TRUE;

		beforePlayer = LEFT;
		if (GetAsyncKeyState('S'))
		{
			g_pPlayer.LEFT = FALSE;
			currentPlayer = UPLEFT;
			beforePlayer = currentPlayer;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		g_pPlayer.Vec.x += speed;

		g_pPlayer.LEFT = FALSE;
		g_pPlayer.RIGHT = TRUE;

		beforePlayer = RIGHT;
		if (GetAsyncKeyState('S'))
		{
			g_pPlayer.RIGHT = FALSE;
			currentPlayer = UPRIGHT;
			beforePlayer = currentPlayer;
		}
	}
	else if (GetAsyncKeyState('S'))
	{
		currentPlayer = UP;
		if (GetAsyncKeyState(VK_LEFT))
		{
			currentPlayer = UPLEFT;
			beforePlayer = currentPlayer;
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			currentPlayer = UPRIGHT;
			beforePlayer = currentPlayer;
		}
	}

	//Jump sys
	if (currentPlayer == UP)
	{
		g_pPlayer.Vec.y += Grav;
		Grav += 0.8;
	}
	else if (currentPlayer == UPLEFT)
	{
		g_pPlayer.Vec.y += Grav;
		Grav += 0.8;

		g_pPlayer.Vec.x -= 0.01f;
	}
	else if (currentPlayer == UPRIGHT)
	{
		g_pPlayer.Vec.y += Grav;
		Grav += 0.8;

		g_pPlayer.Vec.x += 0.01f;
	}
	else if (g_pPlayer.DOWN == TRUE)
	{
		Grav = 15.0f;
		g_pPlayer.Vec.y += Grav;

		Grav += 0.8;
	}

	if (g_pPlayer.GROUND == TRUE)
	{
		if (g_pPlayer.Vec.y >= 240.0f)
		{
			g_pPlayer.GROUND = FALSE;

			g_pPlayer.Vec.y = 240.0f;
			currentPlayer = STAND;

			Grav = -20.0f;
		}
	}

	if (g_pPlayer.Vec.y > 400.0f)
	{
		g_pPlayer.Vec.y = 400.0f;
		currentPlayer = STAND;

		Grav = -20.0f;
	}

	//Hit Ani
	if (g_pPlayer.HIT == TRUE)
	{
		Anitime += 1.0f;
		if (Anitime > 10)
		{
			g_pPlayer.HIT = FALSE;
			Anitime = 0.0f;
		}
	}
	//=================================================

	//container

	for (int i = 0; i < 3; i++)
	{
		if (g_pPlayer.Vec.x > g_pContainer[i].Vec.x + 235 ||
			g_pPlayer.Vec.x + 65 < g_pContainer[i].Vec.x ||
			g_pPlayer.Vec.y > g_pContainer[i].Vec.y + 200 ||
			g_pPlayer.Vec.y + 120 < g_pContainer[i].Vec.y)
		{

		}
		else
		{
			if (g_pPlayer.Vec.x < g_pContainer[i].Vec.x + 200 ||
				g_pPlayer.Vec.x + 30 > g_pContainer[i].Vec.x)
			{
				if (g_pPlayer.Vec.y + 90 <= g_pContainer[i].Vec.y)
				{
					g_pPlayer.GROUND = TRUE;
				}
			}
		}

		if (g_pPlayer.GROUND == TRUE)
		{
			if (g_pPlayer.Vec.x + 30 <= g_pContainer[i].Vec.x ||
				g_pPlayer.Vec.x >= g_pContainer[i].Vec.x + 200)
			{
				g_pPlayer.DOWN = TRUE;
			}
		}
	}

	//=================================================


	//Screen Scroll & Limit line
	if (g_pPlayer.Vec.x + g_pPlayer.rc.bottom > 700.0f)
	{
		g_pPlayer.Vec.x = 700 - g_pPlayer.rc.bottom;

		g_pBacks1_1.Vec.x -= 4.5f;
		g_pBacks1_2.Vec.x -= 4.5f;

		g_pContainer[0].Vec.x -= 4.5f;
		g_pContainer[1].Vec.x -= 4.5f;
		g_pContainer[2].Vec.x -= 4.5f;

		for (int i = 0; i < 100; i++)
		{
			if (g_pEnemy[i].Visible == TRUE)
			{
				g_pEnemy[i].Vec.x -= 4.5f;
				for (int j = 0; j < 10; j++)
				{
					g_pEnemy[i].Bullet[j].Vec.x -= 4.5f;
				}
			}
		}

		for (int i = 0; i < 100; i++)
		{
			if (g_pBullet[i].Visible == TRUE)
			{
				g_pBullet[i].Vec.x -= 4.5f;
			}
		}

		for (int i = 0; i < 100; i++)
		{
			if (g_pHeli[i].Visible == TRUE)
			{
				g_pHeli[i].Vec.x -= 4.5f;
				for (int j = 0; j < 10; j++)
				{
					g_pHeli[i].Bullet[j].Vec.x -= 4.5f;
				}
			}
		}

		for (int i = 0; i < 10; i++)
		{
			if (g_pHP_UP[i].Visible == TRUE)
			{
				g_pHP_UP[i].Vec.x -= 4.5f;
			}
		}

		if (g_pBacks1_1.Vec.x < -800)
		{
			g_pBacks1_1.Vec.x += 4.5f;
			g_pBacks1_2.Vec.x += 4.5f;

			g_pContainer[0].Vec.x += 4.5f;
			g_pContainer[1].Vec.x += 4.5f;
			g_pContainer[2].Vec.x += 4.5f;

			for (int i = 0; i < 100; i++)
			{
				if (g_pEnemy[i].Visible == TRUE)
				{
					g_pEnemy[i].Vec.x += 4.5f;
					for (int j = 0; j < 10; j++)
					{
						g_pEnemy[i].Bullet[j].Vec.x += 4.5f;
					}
				}
			}

			for (int i = 0; i < 100; i++)
			{
				if (g_pBullet[i].Visible == TRUE)
				{
					g_pBullet[i].Vec.x += 4.5f;
				}
			}

			for (int i = 0; i < 100; i++)
			{
				if (g_pHeli[i].Visible == TRUE)
				{
					g_pHeli[i].Vec.x += 4.5f;
					for (int j = 0; j < 10; j++)
					{
						g_pHeli[i].Bullet[j].Vec.x += 4.5f;
					}
				}
			}

			for (int i = 0; i < 10; i++)
			{
				if (g_pHP_UP[i].Visible == TRUE)
				{
					g_pHP_UP[i].Vec.x += 4.5f;
				}
			}
		}
	}
	else if (g_pPlayer.Vec.x < 70.0f)
	{
		g_pPlayer.Vec.x = 70.0f;

		g_pBacks1_1.Vec.x += 4.5f;
		g_pBacks1_2.Vec.x += 4.5f;

		g_pContainer[0].Vec.x += 4.5f;
		g_pContainer[1].Vec.x += 4.5f;
		g_pContainer[2].Vec.x += 4.5f;

		for (int i = 0; i < 100; i++)
		{
			if (g_pEnemy[i].Visible == TRUE)
			{
				g_pEnemy[i].Vec.x += 4.5f;
				for (int j = 0; j < 10; j++)
				{
					g_pEnemy[i].Bullet[j].Vec.x += 4.5f;
				}
			}
		}

		for (int i = 0; i < 100; i++)
		{
			if (g_pBullet[i].Visible == TRUE)
			{
				g_pBullet[i].Vec.x += 4.5f;
			}
		}

		for (int i = 0; i < 100; i++)
		{
			if (g_pHeli[i].Visible == TRUE)
			{
				g_pHeli[i].Vec.x += 4.5f;
				for (int j = 0; j < 10; j++)
				{
					g_pHeli[i].Bullet[j].Vec.x += 4.5f;
				}
			}
		}

		for (int i = 0; i < 10; i++)
		{
			if (g_pHP_UP[i].Visible == TRUE)
			{
				g_pHP_UP[i].Vec.x += 4.5f;
			}
		}

		if (g_pBacks1_1.Vec.x > 0)
		{
			g_pBacks1_1.Vec.x -= 4.5f;
			g_pBacks1_2.Vec.x -= 4.5f;

			g_pContainer[0].Vec.x -= 4.5f;
			g_pContainer[1].Vec.x -= 4.5f;
			g_pContainer[2].Vec.x -= 4.5f;

			for (int i = 0; i < 100; i++)
			{
				if (g_pEnemy[i].Visible == TRUE)
				{
					g_pEnemy[i].Vec.x -= 4.5f;
					for (int j = 0; j < 10; j++)
					{
						g_pEnemy[i].Bullet[j].Vec.x -= 4.5f;
					}
				}
			}

			for (int i = 0; i < 100; i++)
			{
				if (g_pBullet[i].Visible == TRUE)
				{
					g_pBullet[i].Vec.x -= 4.5f;
				}
			}

			for (int i = 0; i < 100; i++)
			{
				if (g_pHeli[i].Visible == TRUE)
				{
					g_pHeli[i].Vec.x -= 4.5f;
					for (int j = 0; j < 10; j++)
					{
						g_pHeli[i].Bullet[j].Vec.x -= 4.5f;
					}
				}
			}

			for (int i = 0; i < 10; i++)
			{
				if (g_pHP_UP[i].Visible == TRUE)
				{
					g_pHP_UP[i].Vec.x -= 4.5f;
				}
			}
		}
	}

	//======================================================

	//GunFire
	if (GetAsyncKeyState('A'))
	{
		bullettime += 1.0f;

		if (bullettime > 10)
		{
			g_pBullet[Bulletcount].Visible = TRUE;

			g_pBullet[Bulletcount].Vec.y = -120.0f;

			if (GetAsyncKeyState(VK_LEFT))
			{
				g_pBullet[Bulletcount].Vec.x = g_pPlayer.Vec.x;
				g_pBullet[Bulletcount].Vec.y = g_pPlayer.Vec.y + 70;

				if (GetAsyncKeyState(VK_UP))
				{
					g_pBullet[Bulletcount].upleft = true;
				}
				else if (GetAsyncKeyState(VK_DOWN))
				{
					g_pBullet[Bulletcount].downleft = true;
				}
				else
				{
					g_pBullet[Bulletcount].left = true;
				}
			}
			else if (GetAsyncKeyState(VK_RIGHT))
			{
				g_pBullet[Bulletcount].Vec.x = g_pPlayer.Vec.x + 70;
				g_pBullet[Bulletcount].Vec.y = g_pPlayer.Vec.y + 70;

				if (GetAsyncKeyState(VK_UP))
				{
					g_pBullet[Bulletcount].upright = true;
				}
				else if (GetAsyncKeyState(VK_DOWN))
				{
					g_pBullet[Bulletcount].downright = true;
				}
				else
				{
					g_pBullet[Bulletcount].right = true;
				}
			}
			else if (GetAsyncKeyState(VK_UP))
			{
				g_pBullet[Bulletcount].Vec.x = g_pPlayer.Vec.x + 40;
				g_pBullet[Bulletcount].Vec.y = g_pPlayer.Vec.y + 70;

				if (GetAsyncKeyState(VK_LEFT))
				{
					g_pBullet[Bulletcount].upleft = true;
				}
				else if (GetAsyncKeyState(VK_RIGHT))
				{
					g_pBullet[Bulletcount].upright = true;
				}
				else
				{
					g_pBullet[Bulletcount].up = true;
				}
			}
			else if (GetAsyncKeyState(VK_DOWN))
			{
				g_pBullet[Bulletcount].Vec.x = g_pPlayer.Vec.x + 40;
				g_pBullet[Bulletcount].Vec.y = g_pPlayer.Vec.y + 70;

				if (GetAsyncKeyState(VK_LEFT))
				{
					g_pBullet[Bulletcount].downleft = true;
				}
				else if (GetAsyncKeyState(VK_RIGHT))
				{
					g_pBullet[Bulletcount].downright = true;
				}
				else
				{
					g_pBullet[Bulletcount].down = true;
				}
			}

			if (Bulletcount >= 99)
			{
				Bulletcount = 0;
			}

			bullettime = 0.0f;
			Bulletcount++;
		}
	}
	//==================================================

	//GunMove
	for (int i = 0; i < 100; i++)
	{
		if (g_pBullet[i].Visible == TRUE)
		{
			if (g_pBullet[i].left == true)
			{
				g_pBullet[i].Vec.x -= 10.0f;
			}
			else if (g_pBullet[i].right == true)
			{
				g_pBullet[i].Vec.x += 10.0f;
			}
			else if (g_pBullet[i].up == true)
			{
				g_pBullet[i].Vec.y -= 10.0f;
			}
			else if (g_pBullet[i].upleft == true)
			{
				g_pBullet[i].Vec.x -= 7.1f;
				g_pBullet[i].Vec.y -= 7.1f;
			}
			else if (g_pBullet[i].upright == true)
			{
				g_pBullet[i].Vec.x += 7.1f;
				g_pBullet[i].Vec.y -= 7.1f;
			}
			else if (g_pBullet[i].down == true)
			{
				g_pBullet[i].Vec.y += 10.0f;
			}
			else if (g_pBullet[i].downleft == true)
			{
				g_pBullet[i].Vec.x -= 7.1f;
				g_pBullet[i].Vec.y += 7.1f;
			}
			else if (g_pBullet[i].downright == true)
			{
				g_pBullet[i].Vec.x += 7.1f;
				g_pBullet[i].Vec.y += 7.1f;
			}

			if (g_pBullet[i].Vec.x > 800 || g_pBullet[i].Vec.x < -760 ||
				g_pBullet[i].Vec.y < -25)
			{
				g_pBullet[i].Visible = FALSE;
			}
		}
		else if (g_pBullet[i].Visible == FALSE)
		{
			g_pBullet[i].left = false;
			g_pBullet[i].right = false;
			g_pBullet[i].up = false;
			g_pBullet[i].upleft = false;
			g_pBullet[i].upright = false;
			g_pBullet[i].down = false;
			g_pBullet[i].downleft = false;
			g_pBullet[i].downright = false;
		}
	}
	//==============================================================

	//GrenFire
	if (GetAsyncKeyState('D'))
	{
		Grentime += 1.0f;

		if (Grentime > 25 && GrenCount < 9 && g_pGrend[GrenCount - 1].Visible == FALSE)
		{
			g_pGrend[GrenCount].Visible = TRUE;

			g_pGrend[GrenCount].Vec.x = g_pPlayer.Vec.x + 35;
			g_pGrend[GrenCount].Vec.y = g_pPlayer.Vec.y + 25;

			if (g_pPlayer.RIGHT == TRUE || g_pPlayer.RIGHTRUN == TRUE || currentPlayer == UPRIGHT)
			{
				g_pGrend[GrenCount].right = true;
			}
			else if (g_pPlayer.LEFT == TRUE || g_pPlayer.LEFTRUN == TRUE || currentPlayer == UPLEFT)
			{
				g_pGrend[GrenCount].left = true;
			}
			else if (currentPlayer == UP)
			{
				g_pGrend[GrenCount].down = true;
			}
			else
			{
				g_pGrend[GrenCount].Visible = FALSE;
			}

			Grentime = 0.0f;
			GrenCount++;
		}
	}
	//===================================================

	//GrenMove
	for (int i = 0; i < 5; i++)
	{
		if (g_pGrend[i].Visible == TRUE)
		{
			if (g_pGrend[i].left == true)
			{
				g_pGrend[i].Vec.y += GrenGrav;
				GrenGrav += 1.0f;

				g_pGrend[i].Vec.x -= 5.0f;
			}
			else if (g_pGrend[i].right == true)
			{
				g_pGrend[i].Vec.y += GrenGrav;
				GrenGrav += 1.0f;

				g_pGrend[i].Vec.x += 5.0f;
			}
			else if (g_pGrend[i].down == true)
			{
				g_pGrend[i].Vec.y += GrenGrav;
				GrenGrav += 1.0f;
			}

			if (g_pGrend[i].Vec.y > 550)
			{
				GrenGrav = -15.0f;
				g_pGrend[i].Visible = FALSE;
			}
		}
		else if (g_pGrend[i].Visible == FALSE)
		{
			g_pGrend[i].left = false;
			g_pGrend[i].right = false;
		}
	}
	//=========================================================

	//Enemy sys

	//Respawn
	enemytime += 1.0f;
	if (enemytime > 200)
	{
		g_pEnemy[enemyCount].Visible = TRUE;

		g_pEnemy[enemyCount].Vec.x = (float)(rand() % 700 + 100);
		g_pEnemy[enemyCount].Vec.y = -120.0f;

		if (g_pEnemy[enemyCount].Vec.x < g_pPlayer.Vec.x)
		{
			g_pEnemy[enemyCount].right = true;
			g_pEnemy[enemyCount].left = false;
		}
		else if (g_pEnemy[enemyCount].Vec.x >= g_pPlayer.Vec.x)
		{
			g_pEnemy[enemyCount].left = true;
			g_pEnemy[enemyCount].right = false;
		}

		if (enemyCount >= 99)
		{
			enemyCount = 0;
		}

		enemytime = 0.0f;
		enemyCount++;
	}

	if (score > 400)
	{
		//Respawn
		Helitime += 1.0f;
		if (score > 500)
		{
			Helitime += 1.0f;
		}

		if (Helitime > 300)
		{
			Helitime = 0.0f;

			g_pHeli[HeliCount].Visible = TRUE;

			g_pHeli[HeliCount].Vec.x = 800.0f;
			g_pHeli[HeliCount].Vec.y = 0.0f;

			if (HeliCount >= 99)
			{
				HeliCount = 0;
			}

			HeliCount++;
		}
	}
	//===================================================

	//Ground & Attack Respawn
	for (int i = 0; i < 100; i++)
	{
		if (g_pEnemy[i].Visible == TRUE)
		{
			g_pEnemy[i].Vec.y += 6.5f;

			if (g_pEnemy[i].Vec.y > 400)
			{
				g_pEnemy[i].Vec.y = 400.0f;
				g_pEnemy[i].GROUND = TRUE;
			}
		}
		if (g_pEnemy[i].GROUND == TRUE)
		{
			g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].firetime += 0.5f;

			if (g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].firetime > 30)
			{
				g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].firetime = 0.0f;
				g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].Visible = TRUE;

				g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].Vec.x = g_pEnemy[i].Vec.x + 20;
				g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].Vec.y = g_pEnemy[i].Vec.y + 50;

				if (g_pEnemy[i].left == true)
				{
					g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].left = true;
				}
				else if (g_pEnemy[i].right == true)
				{
					g_pEnemy[i].Bullet[g_pEnemy[i].Bulletcount].right = true;
				}

				if (g_pEnemy[i].Bulletcount >= 9)
				{
					g_pEnemy[i].Bulletcount = 0;
				}

				g_pEnemy[i].Bulletcount++;
			}
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (g_pHeli[i].Visible == TRUE)
		{
			g_pHeli[i].Bullet[g_pHeli[i].Bulletcount].firetime += 0.5f;

			if (g_pHeli[i].Bullet[g_pHeli[i].Bulletcount].firetime > 10)
			{
				g_pHeli[i].Bullet[g_pHeli[i].Bulletcount].firetime = 0.0f;
				g_pHeli[i].Bullet[g_pHeli[i].Bulletcount].Visible = TRUE;

				g_pHeli[i].Bullet[g_pHeli[i].Bulletcount].Vec.x = g_pHeli[i].Vec.x;
				g_pHeli[i].Bullet[g_pHeli[i].Bulletcount].Vec.y = 0.0f;

				if (g_pHeli[i].Bulletcount >= 9)
				{
					g_pHeli[i].Bulletcount = 0;
				}

				g_pHeli[i].Bulletcount++;
			}
		}
	}
	//==================================================

	//AttackMove
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (g_pEnemy[i].Bullet[j].Visible == TRUE)
			{
				if (g_pEnemy[i].Bullet[j].left == true)
				{
					g_pEnemy[i].Bullet[j].Vec.x -= 5.0f;
				}
				else if (g_pEnemy[i].Bullet[j].right == true)
				{
					g_pEnemy[i].Bullet[j].Vec.x += 5.0f;
				}
			}
			else
			{
				g_pEnemy[i].Bullet[j].left = false;
				g_pEnemy[i].Bullet[j].right = false;
			}
		}

		if (g_pEnemy[i].Visible == FALSE)
		{
			g_pEnemy[i].GROUND = FALSE;
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (g_pHeli[i].Visible == TRUE)
		{
			g_pHeli[i].Vec.x -= 7.0f;

			for (int j = 0; j < 10; j++)
			{
				if (g_pHeli[i].Bullet[j].Visible == TRUE)
				{
					g_pHeli[i].Bullet[j].Vec.y += 6.5f;
				}
			}
		}
	}

	//=====================================================

	//item
	if (HP < 3)
	{
		Itemtime += 1.0f;
		if (Itemtime > 100)
		{
			g_pHP_UP[itemcount].Visible = TRUE;

			g_pHP_UP[itemcount].Vec.x = (float)(rand() % 700 + 100);
			g_pHP_UP[itemcount].Vec.y = 0.0f;

			if (itemcount >= 9)
			{
				itemcount = 0;
			}

			Itemtime = 0.0f;
			itemcount++;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (g_pHP_UP[i].Visible == TRUE)
		{
			g_pHP_UP[i].Vec.y += 4.0f;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (g_pHP_UP[i].Visible == TRUE)
		{
			if (g_pPlayer.Vec.x + 10 > g_pHP_UP[i].Vec.x + rc_HPUP.bottom ||
				g_pPlayer.Vec.x + g_pPlayer.rc.bottom - 10 < g_pHP_UP[i].Vec.x ||
				g_pPlayer.Vec.y > g_pHP_UP[i].Vec.y + rc_HPUP.right ||
				g_pPlayer.Vec.y + g_pPlayer.rc.right < g_pHP_UP[i].Vec.y)
			{

			}
			else
			{
				g_pHP_UP[i].Visible = FALSE;
				HP++;
			}
		}
	}
	//==============================================================

	//面倒贸府
	for (int i = 0; i < 100; i++)
	{
		if (g_pEnemy[i].Visible == TRUE)
		{
			for (int check = 0; check < 100; check++)
			{
				if (g_pBullet[check].Visible == TRUE && g_pEnemy[i].GROUND == TRUE)
				{
					if (g_pBullet[check].Vec.x > g_pEnemy[i].Vec.x + rc_Enem.bottom ||
						g_pBullet[check].Vec.x + rc_Bullet.bottom < g_pEnemy[i].Vec.x ||
						g_pBullet[check].Vec.y > g_pEnemy[i].Vec.y + rc_Enem.right ||
						g_pBullet[check].Vec.y + rc_Bullet.right < g_pEnemy[i].Vec.y)
					{

					}
					else
					{
						if (g_pEnemy[i].Hp <= 0)
						{
							g_pEnemy[i].Visible = FALSE;
						}
						g_pBullet[check].Visible = FALSE;
						g_pEnemy[i].Hp -= 2;
						score += 10;
					}
				}
			}

			for (int check = 0; check < 10; check++)
			{
				if (g_pGrend[check].Visible == TRUE && g_pEnemy[i].GROUND == TRUE)
				{
					if (g_pGrend[check].Vec.x > g_pEnemy[i].Vec.x + rc_Enem.bottom ||
						g_pGrend[check].Vec.x + rc_Gren.bottom < g_pEnemy[i].Vec.x ||
						g_pGrend[check].Vec.y > g_pEnemy[i].Vec.y + rc_Enem.right ||
						g_pGrend[check].Vec.y + rc_Gren.right < g_pEnemy[i].Vec.y)
					{

					}
					else
					{
						if (g_pEnemy[i].Hp <= 0)
						{
							g_pEnemy[i].Visible = FALSE;
						}
						g_pGrend[check].Visible = FALSE;
						g_pPlayer.HIT = TRUE;
						g_pBomb.Vec.x = g_pEnemy[i].Vec.x;
						g_pBomb.Vec.y = g_pEnemy[i].Vec.y;
						g_pEnemy[i].Hp -= 100;
						score += 30;
					}
				}
			}

			for (int j = 0; j < 10; j++)
			{
				if (g_pEnemy[i].Bullet[j].Visible == TRUE)
				{
					if (g_pPlayer.Vec.x + 10 > g_pEnemy[i].Bullet[j].Vec.x + rc_Bullet.bottom ||
						g_pPlayer.Vec.x + g_pPlayer.rc.bottom - 10 < g_pEnemy[i].Bullet[j].Vec.x ||
						g_pPlayer.Vec.y > g_pEnemy[i].Bullet[j].Vec.y + rc_Bullet.right ||
						g_pPlayer.Vec.y + g_pPlayer.rc.right < g_pEnemy[i].Bullet[j].Vec.y)
					{

					}
					else
					{
						g_pEnemy[i].Bullet[j].Visible = FALSE;
						HP--;
					}
				}
			}
		}
		if (g_pHeli[i].Visible == TRUE)
		{
			for (int j = 0; j < 10; j++)
			{
				if (g_pHeli[i].Bullet[j].Visible == TRUE)
				{
					if (g_pPlayer.Vec.x + 40 > g_pHeli[i].Bullet[j].Vec.x + rc_Clear.bottom ||
						g_pPlayer.Vec.x + g_pPlayer.rc.bottom - 40 < g_pHeli[i].Bullet[j].Vec.x ||
						g_pPlayer.Vec.y + 50 > g_pHeli[i].Bullet[j].Vec.y + rc_Clear.right ||
						g_pPlayer.Vec.y + g_pPlayer.rc.right - 50 < g_pHeli[i].Bullet[j].Vec.y)
					{

					}
					else
					{
						g_pHeli[i].Bullet[j].Visible = FALSE;
						HP--;
						g_pPlayer.HIT = TRUE;
						g_pBomb.Vec.x = g_pHeli[i].Bullet[j].Vec.x;
						g_pBomb.Vec.y = g_pPlayer.Vec.y;
					}
				}
			}
		}
	}

	if (HP <= 0)
	{
		currentScreen = DIE;
	}
}

void EndingUpdate()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		HP = 5;
		score = 0;
		GrenCount = 0;
		Coin = 5;

		g_pPlayer.Vec.x = 150.0f;
		g_pPlayer.Vec.y = 400.0f;

		g_pBomb.Visible = FALSE;

		g_pWin_start.Visible = FALSE;

		for (int i = 0; i < 5; i++)
		{
			g_pGrend[i].Visible = FALSE;
		}

		for (int i = 0; i < 100; i++)
		{
			g_pBullet[i].Visible = FALSE;

			g_pEnemy[i].Visible = FALSE;
			g_pHeli[i].Visible = FALSE;
		}

		for (int i = 0; i < 10; i++)
		{
			g_pHP_UP[i].Visible = FALSE;
		}

		currentScreen = MENU;
	}
}

void Update()
{
	switch (currentScreen)
	{
	case INTRO:
		IntroUpdate();
		break;
	case MENU:
		MenuUpdate();
		break;
	case GAME1:
		Game1Update();
		break;
	case GAME2:
		Game2Update();
		break;
	case DIE:
		DieUpdate();
		break;
	case LOADING:
		LoadingUpdate();
		break;
	case ENDING:
		EndingUpdate();
		break;
	}
	
	beforeClick = currentClick;
}

void IntroRender()
{
	g_pSprite->Draw(g_pInt_Gun.Tex, &g_pInt_Gun.rc, NULL, &g_pInt_Gun.Vec, 0xfffffffff);
	
	if (g_pTitle.Visible == TRUE)
	{
		g_pSprite->Draw(g_pTitle.Tex, &g_pTitle.rc, NULL, &g_pTitle.Vec, 0xfffffffff);
	}

	if (g_pBreak.Visible == TRUE)
	{
		g_pSprite->Draw(g_pBreak.Tex, &rc_Screen, NULL, &g_pBreak.Vec, 0xfffffffff);
	}
	else if (g_pBreak_2.Visible == TRUE)
	{
		g_pSprite->Draw(g_pBreak_2.Tex, &rc_Screen, NULL, &g_pBreak.Vec, 0xfffffffff);
	}
}

void MenuRender()
{
	if (g_pStart.Visible == TRUE)
	{
		g_pSprite->Draw(g_pStart.Tex, &rc_Screen, NULL, &g_pStart.Vec, 0xfffffffff);
	}
	else if (g_pRank.Visible == TRUE)
	{
		g_pSprite->Draw(g_pRank.Tex, &rc_Screen, NULL, &g_pRank.Vec, 0xfffffffff);
	}
	else if (g_pHowto.Visible == TRUE)
	{
		g_pSprite->Draw(g_pHowto.Tex, &rc_Screen, NULL, &g_pHowto.Vec, 0xfffffffff);
	}
	else if (g_pExit.Visible == TRUE)
	{
		g_pSprite->Draw(g_pExit.Tex, &rc_Screen, NULL, &g_pExit.Vec, 0xfffffffff);
	}
	else if (g_pMenu.Visible == TRUE)
	{
		g_pSprite->Draw(g_pMenu.Tex, &rc_Screen, NULL, &g_pMenu.Vec, 0xfffffffff);
	}

	if (g_pWin_start.Visible == TRUE)
	{
		g_pSprite->Draw(g_pWin_start.Tex, &g_pWin_start.rc, NULL, &g_pWin_start.Vec, 0xfffffffff);
	}
	
	if (g_pWin_Exit.Visible == TRUE)
	{
		g_pSprite->Draw(g_pWin_Exit.Tex, &g_pWin_Exit.rc, NULL, &g_pWin_Exit.Vec, 0xfffffffff);
	}
}

void Game1Render()
{
	g_pSprite->Draw(g_pBacks1_1.Tex, &rc_Screen, NULL, &g_pBacks1_1.Vec, 0xfffffffff);
	g_pSprite->Draw(g_pBacks1_2.Tex, &rc_Screen, NULL, &g_pBacks1_2.Vec, 0xfffffffff);

	g_pSprite->Draw(g_pConTex, &rc_Container, NULL, &g_pContainer[0].Vec, 0xfffffffff);
	g_pSprite->Draw(g_pConTex, &rc_Container, NULL, &g_pContainer[1].Vec, 0xfffffffff);
	g_pSprite->Draw(g_pConTex, &rc_Container, NULL, &g_pContainer[2].Vec, 0xfffffffff);

	for (int i = 0; i < 100; i++)
	{
		if (g_pEnemy[i].Visible == TRUE)
		{
			for (int j = 0; j < 10; j++)
			{
				if (g_pEnemy[i].Bullet[j].Visible == TRUE)
				{
					g_pSprite->Draw(g_pEBulletTex, &rc_Bullet, NULL, &g_pEnemy[i].Bullet[j].Vec, 0xfffffffff);
				}
			}
			if (g_pEnemy[i].left == true)
			{
				g_pSprite->Draw(g_pEnemy_LTex, &rc_Enem, NULL, &g_pEnemy[i].Vec, 0xfffffffff);
			}
			if (g_pEnemy[i].right == true)
			{
				g_pSprite->Draw(g_pEnemy_RTex, &rc_Enem, NULL, &g_pEnemy[i].Vec, 0xfffffffff);
			}
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (g_pBullet[i].Visible == TRUE)
		{
			g_pSprite->Draw(g_pBulletTex, &rc_Bullet, NULL, &g_pBullet[i].Vec, 0xfffffffff);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (g_pGrend[i].Visible == TRUE)
		{
			g_pSprite->Draw(g_pGrenTex, &rc_Gren, NULL, &g_pGrend[i].Vec, 0xfffffffff);
		}
	}

	if (beforePlayer == LEFT)
	{
		g_pSprite->Draw(g_pPlayerTex[0].Tex, &g_pPlayer.rc, NULL, &g_pPlayer.Vec, 0xfffffffff);
	}
	if (beforePlayer == RIGHT)
	{
		g_pSprite->Draw(g_pPlayerTex[1].Tex, &g_pPlayer.rc, NULL, &g_pPlayer.Vec, 0xfffffffff);
	}
	if (beforePlayer == UPLEFT)
	{
		g_pSprite->Draw(g_pPlayerTex[2].Tex, &g_pPlayer.rc, NULL, &g_pPlayer.Vec, 0xfffffffff);
	}
	if (beforePlayer == UPRIGHT)
	{
		g_pSprite->Draw(g_pPlayerTex[3].Tex, &g_pPlayer.rc, NULL, &g_pPlayer.Vec, 0xfffffffff);
	}

	for (int i = 0; i < 100; i++)
	{
		if (g_pHeli[i].Visible == TRUE)
		{
			g_pSprite->Draw(g_pHeliTex, &rc_Heli, NULL, &g_pHeli[i].Vec, 0xfffffffff);

			for (int j = 0; j < 10; j++)
			{
				if (g_pHeli[i].Bullet[j].Visible == TRUE)
				{
					g_pSprite->Draw(g_pClearTex, &rc_Clear, NULL, &g_pHeli[i].Bullet[j].Vec, 0xfffffffff);
				}
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (g_pHP_UP[i].Visible == TRUE)
		{
			g_pSprite->Draw(g_pHP_UPTex, &rc_HPUP, NULL, &g_pHP_UP[i].Vec, 0xfffffffff);
		}
	}

	if (g_pPlayer.HIT == TRUE)
	{
		g_pSprite->Draw(g_pBomb.Tex, &g_pBomb.rc, NULL, &g_pBomb.Vec, 0xfffffffff);
	}

	sprintf(HPStr, "HP : %2d", HP);
	sprintf(ScoreStr, "SCORE : %2d", score);
	RECT HPRect = { 50, 20, 0, 0 };
	RECT ScoreRect = { 550, 20, 0, 0 };
	Font->DrawTextA(g_pSprite, HPStr, -1, &HPRect, DT_NOCLIP, D3DCOLOR_XRGB(50, 255, 200));
	Font->DrawTextA(g_pSprite, ScoreStr, -1, &ScoreRect, DT_NOCLIP, D3DCOLOR_XRGB(50, 255, 200));
}

void DieRender()
{
	g_pSprite->Draw(g_pDie.Tex, &rc_Screen, NULL, &g_pDie.Vec, 0xfffffffff);

	sprintf(CoinStr, "Coin : %2d", Coin);
	RECT CoinRect = { 330, 400, 0, 0 };
	Font->DrawTextA(g_pSprite, CoinStr, -1, &CoinRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 200));
}

void Game2Rener()
{
	g_pSprite->Draw(g_pBack_s2_1, &rc_Screen, NULL, &g_pBacks1_1.Vec, 0xfffffffff);
	g_pSprite->Draw(g_pBack_s2_1, &rc_Screen, NULL, &g_pBacks1_2.Vec, 0xfffffffff);

	g_pSprite->Draw(g_pConTex, &rc_Container, NULL, &g_pContainer[0].Vec, 0xfffffffff);
	g_pSprite->Draw(g_pConTex, &rc_Container, NULL, &g_pContainer[1].Vec, 0xfffffffff);
	g_pSprite->Draw(g_pConTex, &rc_Container, NULL, &g_pContainer[2].Vec, 0xfffffffff);

	for (int i = 0; i < 100; i++)
	{
		if (g_pEnemy[i].Visible == TRUE)
		{
			for (int j = 0; j < 10; j++)
			{
				if (g_pEnemy[i].Bullet[j].Visible == TRUE)
				{
					g_pSprite->Draw(g_pEBulletTex, &rc_Bullet, NULL, &g_pEnemy[i].Bullet[j].Vec, 0xfffffffff);
				}
			}
			if (g_pEnemy[i].left == true)
			{
				g_pSprite->Draw(g_pEnemy_LTex, &rc_Enem, NULL, &g_pEnemy[i].Vec, 0xfffffffff);
			}
			if (g_pEnemy[i].right == true)
			{
				g_pSprite->Draw(g_pEnemy_RTex, &rc_Enem, NULL, &g_pEnemy[i].Vec, 0xfffffffff);
			}
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (g_pBullet[i].Visible == TRUE)
		{
			g_pSprite->Draw(g_pBulletTex, &rc_Bullet, NULL, &g_pBullet[i].Vec, 0xfffffffff);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (g_pGrend[i].Visible == TRUE)
		{
			g_pSprite->Draw(g_pGrenTex, &rc_Gren, NULL, &g_pGrend[i].Vec, 0xfffffffff);
		}
	}

	if (beforePlayer == LEFT)
	{
		g_pSprite->Draw(g_pPlayerTex[0].Tex, &g_pPlayer.rc, NULL, &g_pPlayer.Vec, 0xfffffffff);
	}
	if (beforePlayer == RIGHT)
	{
		g_pSprite->Draw(g_pPlayerTex[1].Tex, &g_pPlayer.rc, NULL, &g_pPlayer.Vec, 0xfffffffff);
	}
	if (beforePlayer == UPLEFT)
	{
		g_pSprite->Draw(g_pPlayerTex[2].Tex, &g_pPlayer.rc, NULL, &g_pPlayer.Vec, 0xfffffffff);
	}
	if (beforePlayer == UPRIGHT)
	{
		g_pSprite->Draw(g_pPlayerTex[3].Tex, &g_pPlayer.rc, NULL, &g_pPlayer.Vec, 0xfffffffff);
	}

	for (int i = 0; i < 100; i++)
	{
		if (g_pHeli[i].Visible == TRUE)
		{
			g_pSprite->Draw(g_pHeliTex, &rc_Heli, NULL, &g_pHeli[i].Vec, 0xfffffffff);

			for (int j = 0; j < 10; j++)
			{
				if (g_pHeli[i].Bullet[j].Visible == TRUE)
				{
					g_pSprite->Draw(g_pClearTex, &rc_Clear, NULL, &g_pHeli[i].Bullet[j].Vec, 0xfffffffff);
				}
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (g_pHP_UP[i].Visible == TRUE)
		{
			g_pSprite->Draw(g_pHP_UPTex, &rc_HPUP, NULL, &g_pHP_UP[i].Vec, 0xfffffffff);
		}
	}

	if (g_pPlayer.HIT == TRUE)
	{
		g_pSprite->Draw(g_pBomb.Tex, &g_pBomb.rc, NULL, &g_pBomb.Vec, 0xfffffffff);
	}
	

	sprintf(HPStr, "HP : %2d", HP);
	sprintf(ScoreStr, "SCORE : %2d", score);
	RECT HPRect = { 50, 20, 0, 0 };
	RECT ScoreRect = { 550, 20, 0, 0 };
	Font->DrawTextA(g_pSprite, HPStr, -1, &HPRect, DT_NOCLIP, D3DCOLOR_XRGB(50, 255, 200));
	Font->DrawTextA(g_pSprite, ScoreStr, -1, &ScoreRect, DT_NOCLIP, D3DCOLOR_XRGB(50, 255, 200));
}

void EndingRener()
{
	g_pSprite->Draw(g_pEnding.Tex, &rc_Screen, NULL, &g_pEnding.Vec, 0xfffffffff);

	sprintf(ScoreStr, "%2d", score);
	RECT ScoreRect = { 400, 282, 0, 0 };
	Font->DrawTextA(g_pSprite, ScoreStr, -1, &ScoreRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

VOID Render()
{
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		switch (currentScreen)
		{
		case INTRO:
			IntroRender();
			break;
		case MENU:
			MenuRender();
			break;
		case GAME1:
			Game1Render();
			break;
		case DIE:
			if (beforeScreen == GAME1)
			{
				Game1Render();
			}
			else if (beforeScreen == GAME2)
			{
				Game2Rener();
			}
			DieRender();
			break;
		case LOADING:
			Game1Render();
			break;
		case GAME2:
			Game2Rener();
			break;
		case ENDING:
			EndingRener();
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
		CleanUp();
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			CleanUp();
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

INT WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, INT)
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