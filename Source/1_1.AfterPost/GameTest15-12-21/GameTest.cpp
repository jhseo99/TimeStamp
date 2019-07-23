#include<d3d9.h>
#include<d3dx9.h>
#include<stdlib.h>
#include<Windows.h>
#include<strsafe.h>
#include <time.h>
#pragma comment(lib,"winmm.lib")
#pragma warning(disable:4996)

LPDIRECT3D9 g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL; // Our rendering device
LPD3DXFONT Fonts = NULL;

LPD3DXSPRITE g_pSprite;
WNDCLASSEX g_wc;
HWND g_hWnd;

//Texture
LPDIRECT3DTEXTURE9 g_pArrowTex = NULL;
LPDIRECT3DTEXTURE9 g_pArrow_UpTex = NULL;
LPDIRECT3DTEXTURE9 g_pCArrowTex = NULL;
LPDIRECT3DTEXTURE9 g_pCArrow_UpTex = NULL;
LPDIRECT3DTEXTURE9 g_pBulletTex = NULL;
LPDIRECT3DTEXTURE9 g_pBullet_UpTex = NULL;
LPDIRECT3DTEXTURE9 g_pCBulletTex = NULL;
LPDIRECT3DTEXTURE9 g_pCBullet_UpTex = NULL;
LPDIRECT3DTEXTURE9 g_pSolTex = NULL;
LPDIRECT3DTEXTURE9 g_pGenTex = NULL;
LPDIRECT3DTEXTURE9 g_pEBulletTex = NULL;
LPDIRECT3DTEXTURE9 g_pGrenadeTex = NULL;
LPDIRECT3DTEXTURE9 g_pPlayer_b_left = NULL;
LPDIRECT3DTEXTURE9 g_pPlayer_b_right = NULL;
LPDIRECT3DTEXTURE9 g_pPlayer_b_lu = NULL;
LPDIRECT3DTEXTURE9 g_pPlayer_b_ru = NULL;
LPDIRECT3DTEXTURE9 g_pPlayer_g_left = NULL;
LPDIRECT3DTEXTURE9 g_pPlayer_g_right = NULL;
LPDIRECT3DTEXTURE9 g_pPlayer_g_lu = NULL;
LPDIRECT3DTEXTURE9 g_pPlayer_g_ru = NULL;
LPDIRECT3DTEXTURE9 g_pSoldier_right = NULL;
LPDIRECT3DTEXTURE9 g_pHP_UP = NULL;
LPDIRECT3DTEXTURE9 g_pSpeed_UP = NULL;

//RECT
RECT g_pScreenRect;
RECT g_pArrowRect;
RECT g_pArrow_upRect;
RECT g_pBulletRect;
RECT g_pBullet_upRect;
RECT g_pSolRect;
RECT g_pGenRect;
RECT g_pEBullRect;
RECT g_pEGrenRect;
RECT g_pBombRect;
RECT g_pHPRect;
RECT g_pSpeedRect;

ID3DXFont* Font;

// 버튼클릭, 마우스
bool beforeClick = false;
bool currentClick = false;
int g_MouseX = 0;
int g_MouseY = 0;

//System
int p_HP = 5;
int score = 0;

//Jump System
float Gravity = 1.0f;
float veloster = -15.0f;

//Fire Time
float ArrowFire = 0.0f;
float BulletFire = 0.0f;
int check = 0;
float e_BulletFire = 0.0f;
float e_GrenFire = 0.0f;
float Anitime = 0.0f;

//Count
int countArrow = 0;
int countBullet = 0;
int countSol = 0;
int countGen = 0;
int count_eBullet = 0;
int count_Gren = 0;
int countHP = 0;
int countSpeed = 0;

//Respwan
float e_respawn = 0.0f;
float g_respawn = 0.0f;
float HPrespawn = 0.0f;
float Speedrespawn = 0.0f;

//String
char ScoreStr[1000];
char HPStr[1000];
char MoneyStr[1000];
char Moneyint[1000];

//Money
int Money = 0;

//Screen State
enum ScreenState
{
	INTRO,
	MENU,
	HOWTO,
	SHOP,
	EXIT,
	GAME1,
	GAME2,
	ENDING,
	DIE
};
ScreenState currentScreen = INTRO;

//Player State
enum PlayerState
{
	LEFT,
	RIGHT,
	JUMP,
	STAND,
};
PlayerState beforePlayer;
PlayerState currentPlayer = RIGHT;

//Weapon
enum Weapon
{
	BOW,
	GUN,
};
Weapon currentWeapon = BOW;

//Texture Inform
struct TEXTURE
{
	LPDIRECT3DTEXTURE9 Texture = NULL;
	D3DXVECTOR3 vecPos;
	RECT rc;
	BOOL Visble;
	BOOL Hit;
};
TEXTURE g_pIntro;
TEXTURE g_pTitle;
TEXTURE g_pMenu;
TEXTURE g_pBack1;
TEXTURE g_pBack2;
TEXTURE g_pBack3;
TEXTURE g_pHowto;
TEXTURE g_pEnding;
TEXTURE g_pShop;
TEXTURE g_pExit;
TEXTURE g_pPlayer;
TEXTURE g_pBomb[3];
TEXTURE g_pDie;
TEXTURE g_pSucces;
TEXTURE g_pFailed;

//Button
struct BUTTON
{
	RECT rc;
};
BUTTON Start;
BUTTON Shop;
BUTTON Howto;
BUTTON Exit;
BUTTON OK;
BUTTON NO;
BUTTON ShopBow;
BUTTON ShopGun;
BUTTON ShopExit;
BUTTON EndExit;

//Weapon
struct WEAPON
{
	D3DXVECTOR3 vecPos;
	BOOL Visble;
	BOOL RIGHT;
	BOOL LEFT;
	BOOL JUMP;
	BOOL COLOR;
};
WEAPON g_pArrow[100];
WEAPON g_pBullet[100];
WEAPON g_pEBullet[100];
WEAPON g_pEGrenade[100];
WEAPON g_pHpUP[10];
WEAPON g_pSpeedUP[10];

//Enemy
struct ENEMY
{
	D3DXVECTOR3 vecPos;
	int e_HP = 5;
	int e_GenHP = 10;
	BOOL Visble;
	BOOL Turn;
	BOOL Hit;
};
ENEMY g_pSoldier[100];
ENEMY g_pGeneral[100];

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT InitD3D(HWND hWnd);

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
	g_pScreenRect.right = 800;
	g_pScreenRect.bottom = 600;

	g_pTitle.rc.right = 400;
	g_pTitle.rc.bottom = 200;

	g_pHowto.rc.right = 500;
	g_pHowto.rc.bottom = 400;

	g_pExit.rc.right = 400;
	g_pExit.rc.bottom = 200;

	g_pPlayer.rc.right = 90;
	g_pPlayer.rc.bottom = 130;

	g_pArrowRect.right = 83;
	g_pArrowRect.bottom = 15;

	g_pArrow_upRect.right = 15;
	g_pArrow_upRect.bottom = 83;

	g_pBulletRect.right = 23;
	g_pBulletRect.bottom = 12;

	g_pBullet_upRect.right = 12;
	g_pBullet_upRect.bottom = 23;

	g_pSolRect.right = 80;
	g_pSolRect.bottom = 120;

	g_pGenRect.right = 150;
	g_pGenRect.bottom = 100;

	g_pEBullRect.right = 40;
	g_pEBullRect.bottom = 40;

	g_pEGrenRect.right = 100;
	g_pEGrenRect.bottom = 30;

	g_pBombRect.right = 200;
	g_pBombRect.bottom = 100;
	
	g_pHPRect.right = 50;
	g_pHPRect.bottom = 50;

	g_pSpeedRect.right = 50;
	g_pSpeedRect.bottom = 50;

	//Rect Button
	
	Start.rc.left = 259;
	Start.rc.top = 167;
	Start.rc.right = 543;
	Start.rc.bottom = 234;

	Shop.rc.left = 259;
	Shop.rc.top = 246;
	Shop.rc.right = 543;
	Shop.rc.bottom = 313;

	Howto.rc.left = 259;
	Howto.rc.top = 327;
	Howto.rc.right = 543;
	Howto.rc.bottom = 391;

	Exit.rc.left = 259;
	Exit.rc.top = 403;
	Exit.rc.right = 543;
	Exit.rc.bottom = 467;
	
	OK.rc.left = 192;
	OK.rc.top = 295;
	OK.rc.right = 358;
	OK.rc.bottom = 359;

	NO.rc.left = 382;
	NO.rc.top = 295;
	NO.rc.right = 553;
	NO.rc.bottom = 359;
	
	ShopBow.rc.left = 135;
	ShopBow.rc.top = 155;
	ShopBow.rc.right = 371;
	ShopBow.rc.bottom = 388;

	ShopGun.rc.left = 472;
	ShopGun.rc.top = 160;
	ShopGun.rc.right = 712;
	ShopGun.rc.bottom = 388;

	ShopExit.rc.left = 574;
	ShopExit.rc.top = 487;
	ShopExit.rc.right = 710;
	ShopExit.rc.bottom = 555;

	EndExit.rc.left = 570;
	EndExit.rc.top = 480;
	EndExit.rc.right = 750;
	EndExit.rc.bottom = 567;

	//vecPos
	g_pIntro.vecPos.x = 0.0f;
	g_pIntro.vecPos.y = 0.0f;

	g_pMenu.vecPos.x = 0.0f;
	g_pMenu.vecPos.y = 0.0f;

	g_pTitle.vecPos.x = 800.0f;
	g_pTitle.vecPos.y = 400.0f;

	g_pHowto.vecPos.x = 150.0f;
	g_pHowto.vecPos.y = 100.0f;

	g_pShop.vecPos.x = 0.0f;
	g_pShop.vecPos.y = 0.0f;

	g_pExit.vecPos.x = 190.0f;
	g_pExit.vecPos.y = 200.0f;

	g_pBack1.vecPos.x = 0.0f;
	g_pBack1.vecPos.y = 0.0f;

	g_pBack2.vecPos.x = 800.0f;
	g_pBack2.vecPos.y = 0.0f;

	g_pBack3.vecPos.x = 1600.0f;
	g_pBack3.vecPos.y = 0.0f;

	g_pDie.vecPos.x = 0.0f;
	g_pDie.vecPos.y = 0.0f;

	g_pEnding.vecPos.x = 0.0f;
	g_pEnding.vecPos.y = 0.0f;

	g_pPlayer.vecPos.x = 200.0f;
	g_pPlayer.vecPos.y = 380.0f;

	D3DXCreateFont(g_pd3dDevice, 35, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "궁서체", &Font);
}

void LoadData(void)
{
	D3DXCreateTextureFromFile(g_pd3dDevice, "Intro.png", &g_pIntro.Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Title.png", &g_pTitle.Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Menu.png", &g_pMenu.Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Howto.png", &g_pHowto.Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Shop.png", &g_pShop.Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Exit.png", &g_pExit.Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Backs1_1.png", &g_pBack1.Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Backs1_2.png", &g_pBack2.Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Backs1_3.png", &g_pBack3.Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Player_b_right.png", &g_pPlayer_b_right);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Player_b_left.png", &g_pPlayer_b_left);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Player_b_ru.png", &g_pPlayer_b_ru);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Player_b_lu.png", &g_pPlayer_b_lu);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Player_g_right.png", &g_pPlayer_g_right);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Player_g_left.png", &g_pPlayer_g_left);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Player_g_ru.png", &g_pPlayer_g_ru);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Player_g_lu.png", &g_pPlayer_g_lu);
	D3DXCreateTextureFromFile(g_pd3dDevice, "arrow.png", &g_pArrowTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "arrow_up.png", &g_pArrow_UpTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Bullet.png", &g_pBulletTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Bullet_up.png", &g_pBullet_UpTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "carrow.png", &g_pCArrowTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "carrow_up.png", &g_pCArrow_UpTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "cBullet.png", &g_pCBulletTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "cBullet_up.png", &g_pCBullet_UpTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Soldier.png", &g_pSolTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Soldier_right.png", &g_pSoldier_right);
	D3DXCreateTextureFromFile(g_pd3dDevice, "General.png", &g_pGenTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "eBullet.png", &g_pEBulletTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Grenade.png", &g_pGrenadeTex);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Bomb_1.png", &g_pBomb[0].Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Bomb_2.png", &g_pBomb[1].Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Bomb_3.png", &g_pBomb[2].Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "HP.png", &g_pHP_UP);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Speed.png", &g_pSpeed_UP);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Die.png", &g_pDie.Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Ending.png", &g_pEnding.Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Succes.png", &g_pSucces.Texture);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Failed.png", &g_pFailed.Texture);
}

HRESULT InitD3D(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
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
	ShowWindow(g_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(g_hWnd);
}

void IntroUpdate()
{
	g_pTitle.vecPos.x -= 20;

	if (g_pTitle.vecPos.x == 160)
	{
		g_pTitle.vecPos.x += 20;
		
		if ((beforeClick == true) && (currentClick == false))
		{
			currentScreen = MENU;
		}
	}
}

void MenuUpdate()
{
	if ((beforeClick == true) && (currentClick == false))
	{
		if ((g_MouseX > Start.rc.left) && (g_MouseX < Start.rc.right) &&
			(g_MouseY > Start.rc.top) && (g_MouseY < Start.rc.bottom))
		{
			currentScreen = GAME1;
		}

		else if ((g_MouseX > Howto.rc.left) && (g_MouseX < Howto.rc.right) &&
			(g_MouseY > Howto.rc.top) && (g_MouseY < Howto.rc.bottom))
		{
			currentScreen = HOWTO;
		}

		else if ((g_MouseX > Shop.rc.left) && (g_MouseX < Shop.rc.right) &&
			(g_MouseY > Shop.rc.top) && (g_MouseY < Shop.rc.bottom))
		{
			currentScreen = SHOP;
		}
		else if ((g_MouseX > Exit.rc.left) && (g_MouseX < Exit.rc.right) &&
			(g_MouseY > Exit.rc.top) && (g_MouseY < Exit.rc.bottom))
		{
			currentScreen = EXIT;
		}
	}

}

void HowToUpdate()
{
	if ((beforeClick == true) && (currentClick == false))
	{
		currentScreen = MENU;
	}
}

void ShopUpdate()
{
	if ((beforeClick == true) && (currentClick == false))
	{
		if ((g_MouseX > ShopBow.rc.left) && (g_MouseX < ShopBow.rc.right) &&
			(g_MouseY > ShopBow.rc.top) && (g_MouseY < ShopBow.rc.bottom))
		{
			if (Money >= 1500)
			{
				g_pSucces.Visble = TRUE;

				Money -= 1500;
				for (int i = 0; i < 100; i++)
				{
					g_pArrow[i].COLOR = TRUE;
				}
			}
			else
			{
				g_pFailed.Visble = TRUE;
			}
		}

		else if ((g_MouseX > ShopGun.rc.left) && (g_MouseX < ShopGun.rc.right) &&
			(g_MouseY > ShopGun.rc.top) && (g_MouseY < ShopGun.rc.bottom))
		{
			if (Money >= 2500)
			{
				g_pSucces.Visble = TRUE;

				Money -= 2500;
				for (int i = 0; i < 100; i++)
				{
					g_pBullet[i].COLOR = TRUE;
				}

			}
			else
			{
				g_pFailed.Visble = TRUE;
			}
		}

		else if ((g_MouseX > ShopExit.rc.left) && (g_MouseX < ShopExit.rc.right) &&
			(g_MouseY > ShopExit.rc.top) && (g_MouseY < ShopExit.rc.bottom))
		{
			currentScreen = MENU;
		}
	}
}

void ExitUpdate()
{
	if ((beforeClick == true) && (currentClick == false))
	{
		
		if ((g_MouseX > OK.rc.left) && (g_MouseX < OK.rc.right) &&
			(g_MouseY > OK.rc.top) && (g_MouseY < OK.rc.bottom))
		{
			Cleanup();
			PostQuitMessage(0);
		}
		else if ((g_MouseX > NO.rc.left) && (g_MouseX < NO.rc.right) &&
				(g_MouseY > NO.rc.top) && (g_MouseY < NO.rc.bottom))
		{
			currentScreen = MENU;
		}
	}
}

void Game1Update()
{
	//Player

	//=====================Move===================================
	int speed = 5;

	if (GetAsyncKeyState(VK_SPACE) && 0x8000)
	{
		currentPlayer = JUMP;
	}
	else if (GetAsyncKeyState(VK_LEFT) && (currentPlayer != JUMP) && 0x8000)
	{
		currentPlayer = LEFT;
		beforePlayer = currentPlayer;
		g_pPlayer.vecPos.x -= speed;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && (currentPlayer != JUMP) && 0x8000)
	{
		currentPlayer = RIGHT;
		beforePlayer = currentPlayer;
		g_pPlayer.vecPos.x += speed;
	}
	//============================================================


	//===================Jump=====================================
	if (currentPlayer == JUMP)
	{
		g_pPlayer.vecPos.y += veloster;
		veloster += Gravity;
	}
	if (g_pPlayer.vecPos.y > 380)
	{
		Gravity = 1.0f;
		veloster = -15.0f;
		g_pPlayer.vecPos.y = 380.0f;

		currentPlayer = STAND;

	}
	//=============================================================

	//Attack

	//===============Bow======================================
	//respawn
	if (currentWeapon == BOW)
	{
		ArrowFire += 1.0f;

		if (ArrowFire > 15)
		{
			g_pArrow[countArrow].Visble = TRUE;
			if (currentPlayer == RIGHT)
			{
				g_pArrow[countArrow].RIGHT = TRUE;
				g_pArrow[countArrow].vecPos.y = g_pPlayer.vecPos.y + 40;
				g_pArrow[countArrow].vecPos.x = g_pPlayer.vecPos.x + 30;
			}
			else if (currentPlayer == LEFT)
			{
				g_pArrow[countArrow].LEFT = TRUE;
				g_pArrow[countArrow].vecPos.y = g_pPlayer.vecPos.y + 40;
				g_pArrow[countArrow].vecPos.x = g_pPlayer.vecPos.x - 60;
			}
			else if (currentPlayer == JUMP)
			{
				g_pArrow[countArrow].JUMP = TRUE;
				g_pArrow[countArrow].vecPos.y = g_pPlayer.vecPos.y + 50;
				g_pArrow[countArrow].vecPos.x = g_pPlayer.vecPos.x + 20;
			}
			else
			{
				g_pArrow[countArrow].Visble = FALSE;
			}
			if (countArrow >= 99)
			{
				countArrow = 0;
			}
			ArrowFire = 0.0f;
			countArrow++;
		}
		//Move
		for (int i = 0; i < 100; i++)
		{
			if (g_pArrow[i].Visble == TRUE)
			{
				if (g_pArrow[i].RIGHT == TRUE)
				{
					g_pArrow[i].vecPos.x += 12.5;
				}
				else if (g_pArrow[i].LEFT == TRUE)
				{
					g_pArrow[i].vecPos.x -= 12.5;
				}
				else if (g_pArrow[i].JUMP == TRUE)
				{
					g_pArrow[i].vecPos.y -= 12.5;
				}
			}
			if (g_pArrow[i].vecPos.x > 850 || g_pArrow[i].vecPos.x < -700 ||
				g_pArrow[i].vecPos.y < -50)
			{
				g_pArrow[i].Visble = FALSE;
				if (g_pArrow[i].Visble == FALSE)
				{
					g_pArrow[i].RIGHT = FALSE;
					g_pArrow[i].LEFT = FALSE;
					g_pArrow[i].JUMP = FALSE;
				}
			}
		}
		if (score >= 1000)
		{
			currentWeapon = GUN;

			for (int i = 0; i < 100; i++)
			{
				g_pArrow[i].Visble = FALSE;
				g_pArrow[i].RIGHT = FALSE;
				g_pArrow[i].LEFT = FALSE;
				g_pArrow[i].JUMP = FALSE;
			}

		}
	}
	//=========================================================


	//====================Gun==================================
	//respawn
	else if (currentWeapon == GUN)
	{
		BulletFire += 1.0f;
		if (BulletFire > 15)
		{
			g_pBullet[countBullet].Visble = TRUE;
			if (currentPlayer == RIGHT)
			{
				g_pBullet[countBullet].RIGHT = TRUE;
				g_pBullet[countBullet].vecPos.y = g_pPlayer.vecPos.y + 40;
				g_pBullet[countBullet].vecPos.x = g_pPlayer.vecPos.x + 65;
			}
			else if (currentPlayer == LEFT)
			{
				g_pBullet[countBullet].LEFT = TRUE;
				g_pBullet[countBullet].vecPos.y = g_pPlayer.vecPos.y + 40;
				g_pBullet[countBullet].vecPos.x = g_pPlayer.vecPos.x - 5;
			}
			else if (currentPlayer == JUMP)
			{
				g_pBullet[countBullet].JUMP = TRUE;
				g_pBullet[countBullet].vecPos.y = g_pPlayer.vecPos.y + 40;
				g_pBullet[countBullet].vecPos.x = g_pPlayer.vecPos.x + 20;
			}
			else
			{
				g_pBullet[countBullet].Visble = FALSE;
			}
			if (countBullet >= 99)
			{
				countBullet = 0;
			}

			BulletFire = 0.0f;
			countBullet++;
		}
		//Move
		for (int i = 0; i < 100; i++)
		{
			if (g_pBullet[i].Visble == TRUE)
			{
				if (g_pBullet[i].RIGHT == TRUE)
				{
					g_pBullet[i].vecPos.x += 12.0;
				}
				else if (g_pBullet[i].LEFT == TRUE)
				{
					g_pBullet[i].vecPos.x -= 12.0;
				}
				else if (g_pBullet[i].JUMP == TRUE)
				{
					g_pBullet[i].vecPos.y -= 12.0;
				}
			}
			if (g_pBullet[i].vecPos.x > 850 || g_pBullet[i].vecPos.x < -700 ||
				g_pBullet[i].vecPos.y < -50)
			{
				g_pBullet[i].Visble = FALSE;
				if (g_pBullet[i].Visble == FALSE)
				{
					g_pBullet[i].RIGHT = FALSE;
					g_pBullet[i].LEFT = FALSE;
					g_pBullet[i].JUMP = FALSE;
				}
			}
			if (g_pBullet[i].Visble == FALSE)
			{
				g_pBullet[i].RIGHT = FALSE;
				g_pBullet[i].LEFT = FALSE;
				g_pBullet[i].JUMP = FALSE;
			}
		}
	}
	//========================================================================

	//Item
	//======================Respawn==============================
	Speedrespawn += 0.1f;
	if (Speedrespawn > 400)
	{
		g_pSpeedUP[countSpeed].Visble = TRUE;

		srand((unsigned)time(NULL));
		g_pSpeedUP[countSpeed].vecPos.x = (float)(rand() % 300 + 100);
		g_pSpeedUP[countSpeed].vecPos.y = 0.0f;

		if (countSpeed == 10)
		{
			countSpeed = 0;
		}

		Speedrespawn = 0.0f;
		countSpeed++;
	}

	HPrespawn += 0.1f;
	if (HPrespawn > 80)
	{
		g_pHpUP[countHP].Visble = TRUE;

		srand((unsigned)time(NULL));
		g_pHpUP[countHP].vecPos.x = (float)(rand() % 300 + 100);
		g_pHpUP[countHP].vecPos.y = 0.0f;

		if (countHP == 10)
		{
			countHP = 0;
		}

		HPrespawn = 0.0f;
		countHP++;
	}
	//===========================================================

	//=======================Move===========================
	for (int i = 0; i < 10; i++)
	{
		if (g_pHpUP[i].Visble == TRUE)
		{
			g_pHpUP[i].vecPos.y += 8.0f;
		}
		else if (g_pSpeedUP[i].Visble == TRUE)
		{
			g_pSpeedUP[i].vecPos.y += 8.0f;
		}
		//delete
		if (g_pHpUP[i].vecPos.y > 450.0f)
		{
			g_pHpUP[i].vecPos.y -= 8.0f;
		}
		else if (g_pSpeedUP[i].vecPos.y > 450.0f)
		{
			g_pSpeedUP[i].vecPos.y -= 8.0f;
		}
	}
	//=====================================================

	//Enemy System

	//===============MakeEnemy===========================
	//enemy respawn
	e_respawn += 0.1f;
	if (e_respawn > 20)
	{
		g_pSoldier[countSol].Visble = TRUE;
		
		g_pSoldier[countSol].vecPos.y = 390.0f;
		g_pSoldier[countSol].vecPos.x = 800.0f;

		if (countSol == 100)
		{
			countSol = 0;
		}

		countSol++;
		e_respawn = 0.0f;
	}
	//======================================================


	//================enemy move============================
	for (int i = 0; i < 100; i++)
	{
		if (g_pSoldier[i].Visble == TRUE && g_pEBullet[count_eBullet].Visble == FALSE)
		{
			if (g_pSoldier[i].Turn == FALSE)
			{
				g_pSoldier[i].vecPos.x -= 5;

				if (g_pSoldier[i].vecPos.x < 0)
				{
					g_pSoldier[i].Turn = TRUE;
				}
			}
			else if (g_pSoldier[i].Turn == TRUE)
			{
				g_pSoldier[i].vecPos.x += 5;

				if (g_pSoldier[i].vecPos.x > 780)
				{
					g_pSoldier[i].Turn = FALSE;
				}
			}
		}
	}
	//=========================================================


	//===============enemy Weapon===========================
	e_BulletFire += 0.1f;

	if (e_BulletFire > 20)
	{
		
		g_pEBullet[count_eBullet].Visble = TRUE;

		
		g_pEBullet[count_eBullet].vecPos.x = 800.0f;
		g_pEBullet[count_eBullet].vecPos.y = 450 ;

		if (count_eBullet == 100)
		{
			count_eBullet = 0;
		}
		
		count_eBullet++;
		e_BulletFire = 0.0f;
	}
	//=======================================================


	//==================Enemy_Weapon_Move=====================
	for (int i = 0; i < 100; i++)
	{
		if (g_pEBullet[i].Visble == TRUE)
		{
			g_pEBullet[i].vecPos.x -= 15.0f;
			if (score >= 1200)
			{
				g_pEBullet[i].vecPos.x -= 10.0f;
			}
		}

		if (g_pEBullet[i].vecPos.x > 800 || g_pEBullet[i].vecPos.x < 0)
		{
			g_pEBullet[i].Visble = FALSE;
		}
	}
	//==========================================================

	if (score >= 2000)
	{
		//======================Mack_boss==========================
		g_respawn += 0.1f;
		if (g_respawn > 50 && g_pGeneral[countGen].Visble == FALSE)
		{
			g_pGeneral[countGen].Visble = TRUE;

			g_pGeneral[countGen].vecPos.y = 20.0f;
			g_pGeneral[countGen].vecPos.x = 800.0f;

			if (countGen == 100)
			{
				countGen = 0;
			}

			countGen++;
			g_respawn = 0.0f;
		}
		//=========================================================

		//===============enemy move=============================
		for (int i = 0; i < 100; i++)
		{
			if (g_pGeneral[i].Visble == TRUE && g_pEGrenade[count_eBullet].Visble == FALSE)
			{
				if (g_pGeneral[i].Turn == FALSE)
				{
					g_pGeneral[i].vecPos.x -= 5;

					if (g_pGeneral[i].vecPos.x < 0)
					{
						g_pGeneral[i].Turn = TRUE;
					}
				}
				else if (g_pGeneral[i].Turn == TRUE)
				{
					g_pGeneral[i].vecPos.x += 5;

					if (g_pGeneral[i].vecPos.x > 780)
					{
						g_pGeneral[i].Turn = FALSE;
					}
				}
			}
		}
		//=========================================================

		//==================enemy Weapon==========================
		e_GrenFire += 1.0f;

		if (e_GrenFire > 100)
		{

			g_pEGrenade[count_Gren].Visble = TRUE;

			srand((unsigned)time(NULL));
			g_pEGrenade[count_Gren].vecPos.x = (float)(rand() % 400 + 100);
			g_pEGrenade[count_Gren].vecPos.y = 0.0f;

			if (count_Gren == 100)
			{
				count_Gren = 0;
			}

			count_Gren++;
			e_GrenFire = 0.0f;
		}
		//=========================================================

		//======================Move==============================
		for (int i = 0; i < 100; i++)
		{
			if (g_pEGrenade[i].Visble == TRUE)
			{
				g_pEGrenade[i].vecPos.y += 15.0f;
			}

			if (g_pEGrenade[i].vecPos.y > 500)
			{
				g_pEGrenade[i].Visble = FALSE;
			}
		}
		//=========================================================

	}
	//===================================================


	//=======================충돌처리=========================
	for (int i = 0; i < 100; i++)
	{
		if (g_pEBullet[i].Visble == TRUE)
		{
			if (g_pPlayer.vecPos.x + 10 > g_pEBullet[i].vecPos.x + g_pEBullRect.bottom ||
				g_pPlayer.vecPos.x + g_pPlayer.rc.bottom  - 10 < g_pEBullet[i].vecPos.x ||
				g_pPlayer.vecPos.y > g_pEBullet[i].vecPos.y + g_pEBullRect.right ||
				g_pPlayer.vecPos.y + g_pPlayer.rc.right < g_pEBullet[i].vecPos.y)
			{
				
			}
			else
			{
				g_pEBullet[i].Visble = FALSE;
				g_pPlayer.Hit = TRUE;
				p_HP--;
			}
		}
		if (g_pEGrenade[i].Visble == TRUE)
		{
			if (g_pPlayer.vecPos.x + 30 > g_pEGrenade[i].vecPos.x + 90 ||
				g_pPlayer.vecPos.x + 40 < g_pEGrenade[i].vecPos.x + 10||
				g_pPlayer.vecPos.y - 10> g_pEGrenade[i].vecPos.y + 25 ||
				g_pPlayer.vecPos.y + 120 < g_pEGrenade[i].vecPos.y + 5)
			{

			}
			else
			{
				g_pEGrenade[i].Visble = FALSE;
				g_pBomb[0].Visble = TRUE;
				g_pPlayer.Hit = TRUE;
				p_HP--;
			}
		}

		if (g_pSpeedUP[i].Visble == TRUE)
		{
			if (g_pPlayer.vecPos.x + 15 > g_pSpeedUP[i].vecPos.x + g_pSpeedRect.bottom ||
				g_pPlayer.vecPos.x + g_pPlayer.rc.bottom - 15 < g_pSpeedUP[i].vecPos.x ||
				g_pPlayer.vecPos.y + 10> g_pSpeedUP[i].vecPos.y + g_pSpeedRect.right ||
				g_pPlayer.vecPos.y + g_pPlayer.rc.right - 10 < g_pSpeedUP[i].vecPos.y)
			{

			}
			else
			{
				g_pSpeedUP[i].JUMP = TRUE;
				
				g_pSpeedUP[i].Visble = FALSE;
			}
		}
		else if (g_pHpUP[i].Visble == TRUE)
		{
			if (g_pPlayer.vecPos.x + 15 > g_pHpUP[i].vecPos.x + g_pHPRect.bottom ||
				g_pPlayer.vecPos.x + g_pPlayer.rc.bottom - 15 < g_pSpeedUP[i].vecPos.x ||
				g_pPlayer.vecPos.y + 10> g_pHpUP[i].vecPos.y + g_pHPRect.right ||
				g_pPlayer.vecPos.y + g_pPlayer.rc.right - 10 < g_pSpeedUP[i].vecPos.y)
			{

			}
			else
			{
				g_pHpUP[i].Visble = FALSE;

				p_HP++;
			}
		}

		if (currentWeapon == BOW)
		{
			for (int check = 0; check < 100; check++)
			{
				if ((g_pArrow[check].Visble == TRUE && g_pSoldier[i].Visble == TRUE))
				{
					if (g_pArrow[check].vecPos.x > g_pSoldier[i].vecPos.x + g_pSolRect.bottom ||
						g_pArrow[check].vecPos.x + g_pArrowRect.bottom < g_pSoldier[i].vecPos.x ||
						g_pArrow[check].vecPos.y > g_pSoldier[i].vecPos.y + g_pSolRect.right ||
						g_pArrow[check].vecPos.y + g_pArrowRect.right < g_pSoldier[i].vecPos.y)
					{

					}
					else
					{
						if (g_pSoldier[i].e_HP < 1)
						{
							g_pSoldier[i].Visble = FALSE;
							g_pSoldier[i].Turn = FALSE;

							score += 100;
							Money += 100;
							g_pSoldier[i].e_HP = 5;
						}
						g_pSoldier[i].Hit = TRUE;
						g_pArrow[check].Visble = FALSE;
						g_pArrow[check].RIGHT = FALSE;
						g_pArrow[check].LEFT = FALSE;
						g_pArrow[check].JUMP = FALSE;
						g_pSoldier[i].e_HP--;
					}
				}
			}
		}
		else if (currentWeapon == GUN)
		{
			for (int check = 0; check < 100; check++)
			{
				if ((g_pBullet[check].Visble == TRUE && g_pSoldier[i].Visble == TRUE))
				{
					if (g_pBullet[check].vecPos.x > g_pSoldier[i].vecPos.x + g_pSolRect.bottom ||
						g_pBullet[check].vecPos.x + g_pBulletRect.bottom < g_pSoldier[i].vecPos.x ||
						g_pBullet[check].vecPos.y > g_pSoldier[i].vecPos.y + g_pSolRect.right ||
						g_pBullet[check].vecPos.y + g_pBulletRect.right < g_pSoldier[i].vecPos.y)
					{
					
					}
					else
					{
						if (g_pSoldier[i].e_HP < 1)
						{
							g_pSoldier[i].Visble = FALSE;
							g_pSoldier[i].Turn = FALSE;

							score += 100;
							Money += 250;
							g_pSoldier[i].e_HP = 5;
						}
						g_pSoldier[i].Hit = TRUE;
						g_pBullet[check].Visble = FALSE;
						g_pBullet[check].RIGHT = FALSE;
						g_pBullet[check].LEFT = FALSE;
						g_pBullet[check].JUMP = FALSE;
						g_pSoldier[i].e_HP -= 1.5;
					}
				}
				if ((g_pBullet[check].Visble == TRUE && g_pGeneral[i].Visble == TRUE))
				{
					if (g_pBullet[check].vecPos.x > g_pGeneral[i].vecPos.x + g_pGenRect.bottom ||
						g_pBullet[check].vecPos.x + g_pBulletRect.bottom < g_pGeneral[i].vecPos.x ||
						g_pBullet[check].vecPos.y > g_pGeneral[i].vecPos.y + g_pGenRect.right ||
						g_pBullet[check].vecPos.y + g_pBulletRect.right < g_pGeneral[i].vecPos.y)
					{

					}
					else
					{
						if (g_pGeneral[i].e_GenHP < 1)
						{
							g_pGeneral[i].Visble = FALSE;
							g_pGeneral[i].Turn = FALSE;

							score += 150;
							Money += 10;
							g_pGeneral[i].e_GenHP = 10;
						}
						g_pGeneral[i].Hit = TRUE;
						g_pBullet[check].Visble = FALSE;
						g_pBullet[check].RIGHT = FALSE;
						g_pBullet[check].LEFT = FALSE;
						g_pBullet[check].JUMP = FALSE;
						g_pGeneral[i].e_GenHP -= 1.5;
					}
				}
			}
		}
	}
	//==========item System====================
	for (int i = 0; i < 10; i++)
	{
		if (g_pSpeedUP[i].JUMP == TRUE)
		{
			if (currentWeapon == BOW)
			{
				ArrowFire += 0.5f;
			}
			else if (currentWeapon == GUN)
			{
				BulletFire += 0.5f;
			}
		}
	}

	//=====================================================


	//===========================================


	//Limit Line & Scroll
	if (g_pPlayer.vecPos.x > 400)
	{
		g_pPlayer.vecPos.x = 400;
		
		g_pBack1.vecPos.x -= 6.0f;
		g_pBack2.vecPos.x -= 6.0f;
		g_pBack3.vecPos.x -= 6.0f;

		if (g_pBack3.vecPos.x <= 0)
		{
			g_pBack1.vecPos.x += 6.0f;
			g_pBack2.vecPos.x += 6.0f;
			g_pBack3.vecPos.x += 6.0f;
		}
	}
	if (g_pPlayer.vecPos.x < 100)
	{
		g_pPlayer.vecPos.x = 100;

		g_pBack1.vecPos.x += 6.0f;
		g_pBack2.vecPos.x += 6.0f;
		g_pBack3.vecPos.x += 6.0f;

		if (g_pBack1.vecPos.x >= 0)
		{
			g_pBack1.vecPos.x -= 6.0f;
			g_pBack2.vecPos.x -= 6.0f;
			g_pBack3.vecPos.x -= 6.0f;
		}
	}

	if (p_HP <= 0)
	{
		currentScreen = DIE;
	}

	if (score > 5500)
	{
		currentScreen = ENDING;
	}
}

void DieUpdate()
{
	if (GetAsyncKeyState('R'))
	{
		p_HP = 5;
		
		currentScreen = GAME1;
	}
	else if (GetAsyncKeyState(VK_RETURN))
	{
		p_HP = 5;
		score = 0;
		for (int i = 0; i < 10; i++)
		{
			g_pSpeedUP[i].JUMP = FALSE;
		}
		
		p_HP = 5;
		score = 0;

		currentWeapon = BOW;
		currentPlayer = RIGHT;
		for (int i = 0; i < 10; i++)
		{
			g_pSpeedUP[i].JUMP = FALSE;
		}

		for (int i = 0; i < 100; i++)
		{
			g_pArrow[i].Visble = FALSE;
			g_pBullet[i].Visble = FALSE;

			g_pSoldier[i].Visble = FALSE;
			g_pGeneral[i].Visble = FALSE;
			g_pEGrenade[i].Visble = FALSE;
			g_pEBullet[i].Visble = FALSE;
		}

		currentScreen = MENU;
	}
}

void EndingUpdate()
{
	if ((beforeClick == true) && (currentClick == false))
	{
		if ((g_MouseX > EndExit.rc.left) && (g_MouseX < EndExit.rc.right) &&
			(g_MouseY > EndExit.rc.top) && (g_MouseY < EndExit.rc.bottom))
		{
			p_HP = 5;
			score = 0;
			
			currentWeapon = BOW;
			currentPlayer = RIGHT;
			for (int i = 0; i < 10; i++)
			{
				g_pSpeedUP[i].JUMP = FALSE;
			}

			for (int i = 0; i < 100; i++)
			{
				g_pArrow[i].Visble = FALSE;
				g_pBullet[i].Visble = FALSE;
				
				g_pSoldier[i].Visble = FALSE;
				g_pGeneral[i].Visble = FALSE;
				g_pEGrenade[i].Visble = FALSE;
				g_pEBullet[i].Visble = FALSE;
			}
			
			currentScreen = MENU;
		}
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
	case SHOP:
		ShopUpdate();
		break;
	case HOWTO:
		HowToUpdate();
		break;
	case EXIT:
		ExitUpdate();
		break;
	case GAME1:
		Game1Update();
		break;
	case DIE:
		DieUpdate();
		break;
	case ENDING:
		EndingUpdate();
		break;
	}
	beforeClick = currentClick;
}

void IntroRender()
{
	g_pSprite->Draw(g_pIntro.Texture, &g_pScreenRect, NULL, &g_pIntro.vecPos, 0xfffffffff);
	g_pSprite->Draw(g_pTitle.Texture, &g_pTitle.rc, NULL, &g_pTitle.vecPos, 0xfffffffff);
}

void MenuRender()
{
	g_pSprite->Draw(g_pMenu.Texture, &g_pScreenRect, NULL, &g_pMenu.vecPos, 0xfffffffff);
}

void HowToRender()
{
	g_pSprite->Draw(g_pMenu.Texture, &g_pScreenRect, NULL, &g_pMenu.vecPos, 0xfffffffff);
	g_pSprite->Draw(g_pHowto.Texture, &g_pHowto.rc, NULL, &g_pHowto.vecPos, 0xfffffffff);
}

void ShopRender()
{
	g_pSprite->Draw(g_pShop.Texture, &g_pScreenRect, NULL, &g_pShop.vecPos, 0xfffffffff);
	if (g_pSucces.Visble == TRUE)
	{
		g_pSprite->Draw(g_pSucces.Texture, &g_pExit.rc, NULL, &g_pExit.vecPos, 0xfffffffff);
	}
	else if (g_pFailed.Visble == TRUE)
	{
		g_pSprite->Draw(g_pFailed.Texture, &g_pExit.rc, NULL, &g_pExit.vecPos, 0xfffffffff);
	}

	if (g_pSucces.Visble == TRUE || g_pFailed.Visble == TRUE)
	{
		if ((beforeClick == true) && (currentClick == false))
		{
			g_pFailed.Visble = FALSE;
			g_pSucces.Visble = FALSE;
		}
	}

	sprintf(Moneyint, "%3d$", Money);
	RECT MoneyRect = { 75, 535, 0, 0 };
	Font->DrawTextA(g_pSprite, Moneyint, -1, &MoneyRect, DT_NOCLIP, D3DCOLOR_XRGB(0, 0, 0));
}

void ExitRender()
{
	g_pSprite->Draw(g_pMenu.Texture, &g_pScreenRect, NULL, &g_pMenu.vecPos, 0xfffffffff);
	g_pSprite->Draw(g_pExit.Texture, &g_pExit.rc, NULL, &g_pExit.vecPos, 0xfffffffff);
}

void Game1Rener()
{
	g_pSprite->Draw(g_pBack1.Texture, &g_pScreenRect, NULL, &g_pBack1.vecPos, 0xfffffffff);
	g_pSprite->Draw(g_pBack2.Texture, &g_pScreenRect, NULL, &g_pBack2.vecPos, 0xfffffffff);
	g_pSprite->Draw(g_pBack3.Texture, &g_pScreenRect, NULL, &g_pBack3.vecPos, 0xfffffffff);
	if (currentPlayer == RIGHT)
	{
		if (currentWeapon == BOW)
		{
			g_pSprite->Draw(g_pPlayer_b_right, &g_pPlayer.rc, NULL, &g_pPlayer.vecPos, 0xfffffffff);
		}
		else if (currentWeapon == GUN)
		{
			g_pSprite->Draw(g_pPlayer_g_right, &g_pPlayer.rc, NULL, &g_pPlayer.vecPos, 0xfffffffff);
		}
		
	}
	else if (currentPlayer == LEFT)
	{
		if (currentWeapon == BOW)
		{
			g_pSprite->Draw(g_pPlayer_b_left, &g_pPlayer.rc, NULL, &g_pPlayer.vecPos, 0xfffffffff);
		}
		else if (currentWeapon == GUN)
		{
			g_pSprite->Draw(g_pPlayer_g_left, &g_pPlayer.rc, NULL, &g_pPlayer.vecPos, 0xfffffffff);
		}
	}
	else
	{
		if (beforePlayer == RIGHT)
		{
			if (currentWeapon == BOW)
			{
				g_pSprite->Draw(g_pPlayer_b_ru, &g_pPlayer.rc, NULL, &g_pPlayer.vecPos, 0xfffffffff);
			}
			else if (currentWeapon == GUN)
			{
				g_pSprite->Draw(g_pPlayer_g_ru, &g_pPlayer.rc, NULL, &g_pPlayer.vecPos, 0xfffffffff);
			}
		}
		else if (beforePlayer == LEFT)
		{
			if (currentWeapon == BOW)
			{
				g_pSprite->Draw(g_pPlayer_b_lu, &g_pPlayer.rc, NULL, &g_pPlayer.vecPos, 0xfffffffff);
			}
			else if (currentWeapon == GUN)
			{
				g_pSprite->Draw(g_pPlayer_g_lu, &g_pPlayer.rc, NULL, &g_pPlayer.vecPos, 0xfffffffff);
			}
		}
	}
	if (g_pPlayer.Hit == TRUE)
	{
		g_pSprite->Draw(g_pPlayer.Texture, &g_pPlayer.rc, NULL, &g_pPlayer.vecPos, 0xffff0000);
		g_pPlayer.Hit = FALSE;
	}
	
	for (int i = 0; i < 100; i++)
	{
		if (g_pArrow[i].Visble == TRUE)
		{
			if (g_pArrow[i].COLOR == FALSE)
			{
				if (g_pArrow[i].JUMP == FALSE)
				{
					g_pSprite->Draw(g_pArrowTex, &g_pArrowRect, NULL, &g_pArrow[i].vecPos, 0xfffffffff);
				}
				else
				{
					g_pSprite->Draw(g_pArrow_UpTex, &g_pArrow_upRect, NULL, &g_pArrow[i].vecPos, 0xfffffffff);
				}
			}
			else if (g_pArrow[i].COLOR == TRUE)
			{
				if (g_pArrow[i].JUMP == FALSE)
				{
					g_pSprite->Draw(g_pCArrowTex, &g_pArrowRect, NULL, &g_pArrow[i].vecPos, 0xfffffffff);
				}
				else
				{
					g_pSprite->Draw(g_pCArrow_UpTex, &g_pArrow_upRect, NULL, &g_pArrow[i].vecPos, 0xfffffffff);
				}
			}
		}
	}
	for (int i = 0; i < 100; i++)
	{
		if (g_pBullet[i].Visble == TRUE)
		{
			if (g_pBullet[i].COLOR == FALSE)
			{
				if (g_pBullet[i].JUMP == FALSE)
				{
					g_pSprite->Draw(g_pBulletTex, &g_pBulletRect, NULL, &g_pBullet[i].vecPos, 0xfffffffff);
				}
				else
				{
					g_pSprite->Draw(g_pBullet_UpTex, &g_pBullet_upRect, NULL, &g_pBullet[i].vecPos, 0xfffffffff);
				}
			}
			else if (g_pBullet[i].COLOR == TRUE)
			{
				if (g_pBullet[i].JUMP == FALSE)
				{
					g_pSprite->Draw(g_pCBulletTex, &g_pBulletRect, NULL, &g_pBullet[i].vecPos, 0xfffffffff);
				}
				else
				{
					g_pSprite->Draw(g_pCBullet_UpTex, &g_pBullet_upRect, NULL, &g_pBullet[i].vecPos, 0xfffffffff);
				}
			}
		}
	}
	for (int i = 0; i < 100; i++)
	{
		if (g_pSoldier[i].Visble == TRUE)
		{
			if (g_pSoldier[i].Turn == FALSE)
			{
				g_pSprite->Draw(g_pSolTex, &g_pSolRect, NULL, &g_pSoldier[i].vecPos, 0xfffffffff);
			}
			else if (g_pSoldier[i].Turn == TRUE)
			{
				g_pSprite->Draw(g_pSoldier_right, &g_pSolRect, NULL, &g_pSoldier[i].vecPos, 0xfffffffff);
			}
			
			if (g_pSoldier[i].Hit == TRUE)
			{
				g_pSprite->Draw(g_pSolTex, &g_pSolRect, NULL, &g_pSoldier[i].vecPos, 0xffff0000);
				g_pSoldier[i].Hit = FALSE;
			}
		}
	}
	for (int i = 0; i < 100; i++)
	{
		if (g_pEBullet[i].Visble == TRUE)
		{
			g_pSprite->Draw(g_pEBulletTex, &g_pEBullRect, NULL, &g_pEBullet[i].vecPos, 0xfffffffff);
		}
	}
	for (int i = 0; i < 100; i++)
	{
		if (g_pGeneral[i].Visble == TRUE)
		{
			g_pSprite->Draw(g_pGenTex, &g_pGenRect, NULL, &g_pGeneral[i].vecPos, 0xfffffffff);
			if (g_pGeneral[i].Hit == TRUE)
			{
				g_pSprite->Draw(g_pGenTex, &g_pGenRect, NULL, &g_pGeneral[i].vecPos, 0xffff0000);
				g_pGeneral[i].Hit = FALSE;
			}

			if (g_pGeneral[i].e_GenHP <= 0)
			{
				g_pBomb[0].vecPos.x = g_pGeneral[i].vecPos.x - 60;
				g_pBomb[1].vecPos.x = g_pGeneral[i].vecPos.x - 60;
				g_pBomb[2].vecPos.x = g_pGeneral[i].vecPos.x - 60;

				g_pBomb[0].vecPos.y = g_pGeneral[i].vecPos.y;
				g_pBomb[1].vecPos.y = g_pGeneral[i].vecPos.y;
				g_pBomb[2].vecPos.y = g_pGeneral[i].vecPos.y;

				Anitime += 1.0f;

				if (Anitime > 0 && Anitime <= 8)
				{
					g_pSprite->Draw(g_pBomb[0].Texture, &g_pBombRect, NULL, &g_pBomb[0].vecPos, 0xfffffffff);
				}
				else if (Anitime > 8 && Anitime <= 15)
				{
					g_pSprite->Draw(g_pBomb[1].Texture, &g_pBombRect, NULL, &g_pBomb[1].vecPos, 0xfffffffff);
				}
				else if (Anitime > 15 && Anitime <= 25)
				{
					g_pSprite->Draw(g_pBomb[2].Texture, &g_pBombRect, NULL, &g_pBomb[2].vecPos, 0xfffffffff);
				}
				else if (Anitime > 25)
				{
					g_pBomb[0].Visble = FALSE;
					Anitime = 0.0f;
				}
			}
		}
	}
	for (int i = 0; i < 100; i++)
	{
		if (g_pEGrenade[i].Visble == TRUE)
		{
			g_pSprite->Draw(g_pGrenadeTex, &g_pEGrenRect, NULL, &g_pEGrenade[i].vecPos, 0xfffffffff);
		}
	}

	if (g_pBomb[0].Visble == TRUE)
	{
		g_pBomb[0].vecPos.x = g_pPlayer.vecPos.x - 50;
		g_pBomb[1].vecPos.x = g_pPlayer.vecPos.x - 50;
		g_pBomb[2].vecPos.x = g_pPlayer.vecPos.x - 50;

		g_pBomb[0].vecPos.y = 375;
		g_pBomb[1].vecPos.y = 375;
		g_pBomb[2].vecPos.y = 375;
		
		Anitime += 1.0f;
		
		if (Anitime > 0 && Anitime <= 8)
		{
			g_pSprite->Draw(g_pBomb[0].Texture, &g_pBombRect, NULL, &g_pBomb[0].vecPos, 0xfffffffff);
		}
		else if (Anitime > 8 && Anitime <= 15)
		{
			g_pSprite->Draw(g_pBomb[1].Texture, &g_pBombRect, NULL, &g_pBomb[1].vecPos, 0xfffffffff);
		}
		else if (Anitime > 15 && Anitime <= 25)
		{
			g_pSprite->Draw(g_pBomb[2].Texture, &g_pBombRect, NULL, &g_pBomb[2].vecPos, 0xfffffffff);
		}
		else if (Anitime > 25)
		{
			g_pBomb[0].Visble = FALSE;
			Anitime = 0.0f;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (g_pHpUP[i].Visble == TRUE)
		{
			g_pSprite->Draw(g_pHP_UP, &g_pHPRect, NULL, &g_pHpUP[i].vecPos, 0xfffffffff);
		}
		else if (g_pSpeedUP[i].Visble == TRUE)
		{
			g_pSprite->Draw(g_pSpeed_UP, &g_pSpeedRect, NULL, &g_pSpeedUP[i].vecPos, 0xfffffffff);
		}
	}

	sprintf(ScoreStr, "SCORE : %2d", score);
	sprintf(HPStr, "HP : %2d", p_HP);
	sprintf(MoneyStr, "MONEY : %2d$", Money);
	RECT ScoreRect = { 550, 20, 0, 0 };
	RECT HPRect = { 50, 20, 0, 0 };
	RECT MoneyRect = { 550, 60, 0, 0 };
	Font->DrawTextA(g_pSprite, ScoreStr, -1, &ScoreRect, DT_NOCLIP, D3DCOLOR_XRGB(50, 255, 200));
	Font->DrawTextA(g_pSprite, HPStr, -1, &HPRect, DT_NOCLIP, D3DCOLOR_XRGB(50, 255, 200));
	Font->DrawTextA(g_pSprite, MoneyStr, -1, &MoneyRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 100));
}

void DieRener()
{
	g_pSprite->Draw(g_pDie.Texture, &g_pScreenRect, NULL, &g_pDie.vecPos, 0xfffffffff);
}

void EndingRender()
{
	g_pSprite->Draw(g_pEnding.Texture, &g_pScreenRect, NULL, &g_pEnding.vecPos, 0xfffffffff);

	sprintf(Moneyint, "%2d$", Money);
	RECT MoneyRect = { 450, 320, 0, 0 };
	Font->DrawTextA(g_pSprite, Moneyint, -1, &MoneyRect, DT_NOCLIP, D3DCOLOR_XRGB(0, 0, 0));
}

VOID Render()
{
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

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
		case HOWTO:
			HowToRender();
			break;
		case SHOP:
			ShopRender();
			break;
		case EXIT:
			ExitRender();
			break;
		case GAME1:
			Game1Rener();
			break;
		case DIE:
			Game1Rener();
			DieRener();
			break;
		case ENDING:
			EndingRender();
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