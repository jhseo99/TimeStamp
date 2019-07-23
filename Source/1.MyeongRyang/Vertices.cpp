#include<d3d9.h>
#include<d3dx9.h>
#include<stdlib.h>
#include<Windows.h>
#include<strsafe.h>
#pragma comment(lib,"winmm.lib")
#pragma warning(disable:4996)

LPDIRECT3D9 g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL; // Our rendering device
LPD3DXFONT Fonts = NULL;

LPD3DXSPRITE g_pSprite;
WNDCLASSEX g_wc;
HWND g_hWnd;

//텍스쳐
LPDIRECT3DTEXTURE9 g_pIntro = NULL;
LPDIRECT3DTEXTURE9 g_pMenu = NULL;
LPDIRECT3DTEXTURE9 g_pInform = NULL;
LPDIRECT3DTEXTURE9 g_pStage_s1_1 = NULL;
LPDIRECT3DTEXTURE9 g_pStage_s1_2 = NULL;
LPDIRECT3DTEXTURE9 g_pStage_s1_3 = NULL;
LPDIRECT3DTEXTURE9 g_pStage_s2_1 = NULL;
LPDIRECT3DTEXTURE9 g_pStage_s2_2 = NULL;
LPDIRECT3DTEXTURE9 g_pRing = NULL;
LPDIRECT3DTEXTURE9 g_pPlayer1 = NULL;
LPDIRECT3DTEXTURE9 g_pPlayer2 = NULL;
LPDIRECT3DTEXTURE9 g_pPlayer3 = NULL;
LPDIRECT3DTEXTURE9 g_pDie = NULL;
LPDIRECT3DTEXTURE9 g_pEnemy = NULL;
LPDIRECT3DTEXTURE9 g_pBullet = NULL;
LPDIRECT3DTEXTURE9 g_pArrow = NULL;
LPDIRECT3DTEXTURE9 g_pItem_up = NULL;
LPDIRECT3DTEXTURE9 g_pItem_HP_UP = NULL;
LPDIRECT3DTEXTURE9 g_pState1 = NULL;
LPDIRECT3DTEXTURE9 g_pState2 = NULL;
LPDIRECT3DTEXTURE9 g_pState3 = NULL;
LPDIRECT3DTEXTURE9 g_pState4 = NULL;
LPDIRECT3DTEXTURE9 g_pState5 = NULL;
LPDIRECT3DTEXTURE9 g_pState6 = NULL;
LPDIRECT3DTEXTURE9 g_pState7 = NULL;
LPDIRECT3DTEXTURE9 g_pState8 = NULL;
LPDIRECT3DTEXTURE9 g_pState9 = NULL;
LPDIRECT3DTEXTURE9 g_pState10 = NULL;
LPDIRECT3DTEXTURE9 g_pShip = NULL;
LPDIRECT3DTEXTURE9 g_pBoss1 = NULL;
LPDIRECT3DTEXTURE9 g_pBoss2 = NULL;
LPDIRECT3DTEXTURE9 g_pBullet2 = NULL;
LPDIRECT3DTEXTURE9 g_pE_Bullet = NULL;
LPDIRECT3DTEXTURE9 g_pE_Bulle2 = NULL;
LPDIRECT3DTEXTURE9 g_pBomb = NULL;
LPDIRECT3DTEXTURE9 g_pSwan = NULL;
LPDIRECT3DTEXTURE9 g_pEnding = NULL;

ID3DXFont* Font;
//screen
RECT rcRect_Back;

//버튼
RECT rcRect_Start;
RECT rcRect_Intro;
RECT rcRect_Inform;
RECT rcRect_Exit;
RECT rcRect_Tuto;

D3DXVECTOR3 vecPosTuto;
//Player
RECT rcRect_Player;
RECT rcRect_Ship;
RECT rcRect_Swan;

D3DXVECTOR3 vecPosPlayer;
D3DXVECTOR3 vecPosBoat;
D3DXVECTOR3 vecPosShip;
D3DXVECTOR3 vecPosSwan;

//Enemy
RECT rcRect_Enemy;
RECT rcRect_Boss;

D3DXVECTOR3 vecPosBoss;
//Weapon
RECT rcRect_Bullet;
RECT rcRect_Arrow;
RECT rcRect_Bullet2;
RECT rcRect_eBullet;

D3DXVECTOR3 vecPosBullet2;

//아이템
RECT rcRect_Item;

//진행도
RECT rcRect_State;

D3DXVECTOR3 vecPosState;
//Bomb
RECT rcRect_Bomb;

D3DXVECTOR3 vecPosBomb;
//all
D3DXVECTOR3 vecCenter;
D3DXVECTOR3 vecPosBack;
D3DXVECTOR3 vecPosGameBack_s1_1;
D3DXVECTOR3 vecPosGameBack_s1_2;
D3DXVECTOR3 vecPosGameBack_s1_3;
D3DXVECTOR3 vecPosGameBack_s2_1;
D3DXVECTOR3 vecPosGameBack_s2_2;
D3DXVECTOR3 vecPosEnding;

int p_hp = 5;
int score = 0;
//화면배열
enum SCREEN_STATE
{
	INTRO_SCREEN,
	MENU_SCREEN,
	INFORM_SCREEN,
	GAME_SCREEN1,
	RING_SCREEN,
	GAME_SCREEN2, 
	DIE_SCREEN,
	ENDING_SCREEN,
};

//초기화면 설정
SCREEN_STATE currentScreen = INTRO_SCREEN;


// 버튼클릭, 마우스
bool beforeButton = false;
bool currentButton = false;
bool beforeClick = false;
bool currentClick = false;
int g_MouseX = 0;
int g_MouseY = 0;


int count_e;
int count_music = 0;
int count_Arrow = 0;
int count_Bullet = 0;
int count_eBullet = 0;
int count_hp = 0;
int count_speedup = 0;
int counthpmax = 5000;
int countspeedmax = 5000;
int count_Bullet2 = 0;
int count_Scene = 0;
int check = 0;
int enemyCount = 0;
int e_bullet_count = 0;
char score_string[100];
char HP_string[100];
float arrowFireTime = 0;
float bulletFireTime = 0;

struct Enemy
{
	BOOL Visible;
	D3DXVECTOR3 Pos;
};
Enemy enemy[100];
Enemy e_Bullet[100];
//현재 플레이어
enum Player
{
	Player1,
	Player2,
	Player3,
};
Player currentPlayer = Player1;

struct Item
{
	BOOL Visible;
	D3DXVECTOR3 Pos;
};
Item Speed_up;
Item HP_UP;

struct Weapon
{
	BOOL Visible;
	D3DXVECTOR3 Pos;
};
Weapon Bullet[100];
Weapon Arrow[100];
Weapon Bullet2;
//=================================================================
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT InitD3D(HWND hWnd);

void InitWin(void)	//이니셜라이즈 윈도우
{
	WNDCLASSEX g_wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"D3D Tutorial", NULL };
	RegisterClassEx(&g_wc);

	// Create the application's window
	g_hWnd = CreateWindow("D3D Tutorial", "MeongRyang",
		WS_OVERLAPPED, 0, 0, 800, 600,
		GetDesktopWindow(), NULL, g_wc.hInstance, NULL);
}

void InitDX(void)
{
	ShowCursor(TRUE);
	InitD3D(g_hWnd);
	D3DXCreateSprite(g_pd3dDevice, &g_pSprite);

	//배경
	rcRect_Back.right = 800;
	rcRect_Back.bottom = 600;

	rcRect_Tuto.right = 500;
	rcRect_Tuto.bottom = 400;

	vecPosGameBack_s1_1.x = 0.0f;
	vecPosGameBack_s1_1.y = 0.0f;
	vecPosGameBack_s1_2.x = 0.0f;
	vecPosGameBack_s1_2.y = -600.0f;
	vecPosGameBack_s1_3.x = 0.0f;
	vecPosGameBack_s1_3.y = -1200.0f;

	vecPosGameBack_s2_1.x = 0.0f;
	vecPosGameBack_s2_1.y = 0.0f;
	vecPosGameBack_s2_2.x = 0.0f;
	vecPosGameBack_s2_2.y = -600.0f;

	vecPosEnding.x = 0.0f;
	vecPosEnding.y = 0.0f;

	vecPosTuto.x = 150.0f;
	vecPosTuto.y = 100.0f;
	//버튼
	rcRect_Start.left = 453;
	rcRect_Start.top = 52;
	rcRect_Start.right = 758;
	rcRect_Start.bottom = 126;

	rcRect_Intro.left = 453;
	rcRect_Intro.top = 157;
	rcRect_Intro.right = 758;
	rcRect_Intro.bottom = 233;

	rcRect_Inform.left = 453;
	rcRect_Inform.top = 266;
	rcRect_Inform.right = 758;
	rcRect_Inform.bottom = 344;

	rcRect_Exit.left = 453;
	rcRect_Exit.top = 374;
	rcRect_Exit.right = 758;
	rcRect_Exit.bottom = 453;

	//플레이어;
	rcRect_Player.right = 128;
	rcRect_Player.bottom = 128;
	rcRect_Ship.right = 80;
	rcRect_Ship.bottom = 150;
	rcRect_Swan.right = 500;
	rcRect_Swan.bottom = 150;

	vecPosPlayer.x = 325.0f;
	vecPosPlayer.y = 400.0f;
	vecPosShip.x = 360.0f;
	vecPosShip.y = 450.0f;
	vecPosSwan.x = 150.0f;
	vecPosSwan.y = 400.0f;

	//적
	rcRect_Enemy.right = 130;
	rcRect_Enemy.bottom = 130;
	rcRect_Boss.right = 600;
	rcRect_Boss.bottom = 100;

	vecPosBoss.x = 100.0f;
	vecPosBoss.y = 0.0f;
	//weapon
	rcRect_Arrow.right = 25;
	rcRect_Arrow.bottom = 125;
	rcRect_Bullet.right = 30;
	rcRect_Bullet.bottom = 30;
	rcRect_Bullet2.right = 80;
	rcRect_Bullet2.bottom = 80;
	rcRect_eBullet.right = 35;
	rcRect_eBullet.bottom = 35;
	

	vecPosBullet2.x = vecPosShip.x;
	vecPosBullet2.y = 350.0f;
	//Item
	rcRect_Item.right = 60;
	rcRect_Item.bottom = 60;

	//state
	rcRect_State.right = 200;
	rcRect_State.bottom = 150;

	vecPosState.x = 600.0f;
	vecPosState.y = 450.f;

	//Bomb
	rcRect_Bomb.right = 600;
	rcRect_Bomb.bottom = 300;

	vecPosBomb.x = 100.0f;
	vecPosBomb.y = 0.0f;
	D3DXCreateFont(g_pd3dDevice, 25, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "궁서체", &Font);
}

void LoadData(void)
{
	D3DXCreateTextureFromFile(g_pd3dDevice, "intro.png", &g_pIntro);
	D3DXCreateTextureFromFile(g_pd3dDevice, "menu.png", &g_pMenu);
	D3DXCreateTextureFromFile(g_pd3dDevice, "s1_1.png", &g_pStage_s1_1);
	D3DXCreateTextureFromFile(g_pd3dDevice, "s1_2.png", &g_pStage_s1_2);
	D3DXCreateTextureFromFile(g_pd3dDevice, "s1_3.png", &g_pStage_s1_3);
	D3DXCreateTextureFromFile(g_pd3dDevice, "ring.png", &g_pRing);
	D3DXCreateTextureFromFile(g_pd3dDevice, "die.png", &g_pDie);
	D3DXCreateTextureFromFile(g_pd3dDevice, "p1.png", &g_pPlayer1);
	D3DXCreateTextureFromFile(g_pd3dDevice, "p2.png", &g_pPlayer2);
	D3DXCreateTextureFromFile(g_pd3dDevice, "p3.png", &g_pPlayer3);
	D3DXCreateTextureFromFile(g_pd3dDevice, "e.png", &g_pEnemy);
	D3DXCreateTextureFromFile(g_pd3dDevice, "arrow.png", &g_pArrow);
	D3DXCreateTextureFromFile(g_pd3dDevice, "bullet.png", &g_pBullet);
	D3DXCreateTextureFromFile(g_pd3dDevice, "i_u.png", &g_pItem_up);
	D3DXCreateTextureFromFile(g_pd3dDevice, "i_h.png", &g_pItem_HP_UP);
	D3DXCreateTextureFromFile(g_pd3dDevice, "map1.png", &g_pState1);
	D3DXCreateTextureFromFile(g_pd3dDevice, "map2.png", &g_pState2);
	D3DXCreateTextureFromFile(g_pd3dDevice, "map3.png", &g_pState3);
	D3DXCreateTextureFromFile(g_pd3dDevice, "map4.png", &g_pState4);
	D3DXCreateTextureFromFile(g_pd3dDevice, "map5.png", &g_pState5);
	D3DXCreateTextureFromFile(g_pd3dDevice, "map6.png", &g_pState6);
	D3DXCreateTextureFromFile(g_pd3dDevice, "map7.png", &g_pState7);
	D3DXCreateTextureFromFile(g_pd3dDevice, "map8.png", &g_pState8);
	D3DXCreateTextureFromFile(g_pd3dDevice, "map9.png", &g_pState9);
	D3DXCreateTextureFromFile(g_pd3dDevice, "map10.png", &g_pState10);
	D3DXCreateTextureFromFile(g_pd3dDevice, "s2_1.png", &g_pStage_s2_1);
	D3DXCreateTextureFromFile(g_pd3dDevice, "s2_2.png", &g_pStage_s2_2);
	D3DXCreateTextureFromFile(g_pd3dDevice, "p_boss.png", &g_pShip);
	D3DXCreateTextureFromFile(g_pd3dDevice, "bullet2.png", &g_pBullet2);
	D3DXCreateTextureFromFile(g_pd3dDevice, "e_boss.png", &g_pBoss1);
	D3DXCreateTextureFromFile(g_pd3dDevice, "e_boss2.png", &g_pBoss2);
	D3DXCreateTextureFromFile(g_pd3dDevice, "e_bullet.png", &g_pE_Bullet);
	D3DXCreateTextureFromFile(g_pd3dDevice, "bomb.png", &g_pBomb);
	D3DXCreateTextureFromFile(g_pd3dDevice, "ship2.png", &g_pSwan);
	D3DXCreateTextureFromFile(g_pd3dDevice, "ending.png", &g_pEnding);
	D3DXCreateTextureFromFile(g_pd3dDevice, "tuto.png", &g_pInform);
}

HRESULT InitD3D(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;	//FALSE = 풀스크린 , TRUE = 창모드
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
	if ((beforeClick == true) && (currentClick == false))
	{
		currentScreen = MENU_SCREEN;
	}
}

void MenuUpdate()
{
	if ((beforeClick == true) && (currentClick == false))
	{
		if ((rcRect_Start.left < g_MouseX) &&
			(rcRect_Start.right > g_MouseX) &&
			(rcRect_Start.top < g_MouseY) &&
			(rcRect_Start.bottom > g_MouseY))
		{
			currentScreen = GAME_SCREEN1;
			PlaySound("Wavs/Techno_1.wav", NULL, SND_ASYNC);
		}
		if ((rcRect_Intro.left < g_MouseX) &&
			(rcRect_Intro.right > g_MouseX) &&
			(rcRect_Intro.top < g_MouseY) &&
			(rcRect_Intro.bottom > g_MouseY))
		{
			currentScreen = INTRO_SCREEN;
		}
		if ((rcRect_Inform.left < g_MouseX) &&
			(rcRect_Inform.right > g_MouseX) &&
			(rcRect_Inform.top < g_MouseY) &&
			(rcRect_Inform.bottom > g_MouseY))
		{
			currentScreen = INFORM_SCREEN;
		}
		if ((rcRect_Exit.left < g_MouseX) &&
			(rcRect_Exit.right > g_MouseX) &&
			(rcRect_Exit.top < g_MouseY) &&
			(rcRect_Exit.bottom > g_MouseY))
		{
			Cleanup();
			PostQuitMessage(0);
		}
	}
}

void InformUpdate()
{
	if ((beforeClick == true) && (currentClick == false))
	{
		currentScreen = MENU_SCREEN;
	}
}

void GameUpdate()
{
	//적 생성
	count_e += 1.5;
	if (count_e > 50)
	{
		count_e = 0;
		check++;

		enemy[enemyCount].Visible = TRUE;
		enemy[enemyCount].Pos.y = 0.0f;
		float x = (float)(rand() % 600 + 100);
		enemy[enemyCount].Pos.x = x;

		enemyCount++;

		if (enemyCount == 100)
		{
			enemyCount = 0;
		}
	}
	for (int i = 0; i < 100; i++)
	{
		if (score < 45)
		{
			//적 이동
			if (enemy[i].Visible == TRUE)
			{
				enemy[i].Pos.y += 10.0f;
			}
		}
		else if (score < 90)
		{
			//적 이동
			if (enemy[i].Visible == TRUE)
			{
				enemy[i].Pos.y += 12.0f;
			}
		}
		else
		{
			//적 이동
			if (enemy[i].Visible == TRUE)
			{
				enemy[i].Pos.y += 16.0f;
			}
		}
		//적 삭제
		if (enemy[i].Visible == TRUE)
		{
			if (enemy[i].Pos.y > 400.0f)
			{
				enemy[i].Visible = FALSE;
				p_hp -= 2;
			}
		}
	}
	//=================================================================
	//배경 스크롤
	vecPosGameBack_s1_1.y += 2.0f;
	vecPosGameBack_s1_2.y += 2.0f;
	vecPosGameBack_s1_3.y += 2.0f;
	if (vecPosGameBack_s1_2.y > 600)
	{
		vecPosGameBack_s1_2.y -= 1200.0f;
	}
	else if (vecPosGameBack_s1_3.y > 600)
	{
		vecPosGameBack_s1_3.y -= 1200.0f;
	}
	//===============================================================
	//이동
	if (p_hp < 1)
	{
		currentScreen = DIE_SCREEN;
		PlaySound("Wavs/heli.wav", NULL, SND_ASYNC);
	}
	else
	{
		if (WM_MOUSEMOVE)
		{
			POINT Pos;
			GetCursorPos(&Pos);
			vecPosPlayer.x = Pos.x;
		}
	}
	//=================================================================
	//화면 밖으로 못나가게 설정
	if (vecPosPlayer.x < 0)
	{
		vecPosPlayer.x = 0;
	}
	else if (vecPosPlayer.x > (800) - (rcRect_Player.right))
	{
		vecPosPlayer.x = (800) - (rcRect_Player.right);
	}
	//=================================================================

	// 충돌처리

	for (int i = 0; i < 100; i++)
	{
		if (Bullet[count_Bullet].Visible == TRUE)
		{
			//충돌 x
			if (enemy[i].Pos.x + rcRect_Enemy.bottom < Bullet[count_Bullet].Pos.x
				|| enemy[i].Pos.x > Bullet[count_Bullet].Pos.x + rcRect_Bullet.bottom
				|| enemy[i].Pos.y > Bullet[count_Bullet].Pos.y + rcRect_Bullet.right
				|| enemy[i].Pos.y + rcRect_Enemy.right < Bullet[count_Bullet].Pos.y)
			{

			}
			//충돌한경우
			else
			{
				if (enemy[i].Visible == TRUE)
				{
					score++;
				}
				enemy[i].Visible = FALSE;
			}
		}
		else if (Arrow[count_Arrow].Visible == TRUE)
		{
			//충돌 x
			if (enemy[i].Pos.x + rcRect_Enemy.bottom < Arrow[count_Arrow].Pos.x
				&& enemy[i].Pos.x > Arrow[count_Arrow].Pos.x + rcRect_Arrow.bottom
				&& enemy[i].Pos.y > Arrow[count_Arrow].Pos.y + rcRect_Arrow.right
				&& enemy[i].Pos.y + rcRect_Enemy.right < Arrow[count_Arrow].Pos.y)
			{
				if (enemy[i].Visible == TRUE)
				{
					score++;
				}
				enemy[i].Visible = FALSE;
			}
			//충돌한경우
			else
			{

			}
		}
		else
		{
			//충돌 x
			if (enemy[i].Pos.x + rcRect_Enemy.bottom < vecPosPlayer.x
				|| enemy[i].Pos.x > vecPosPlayer.x + rcRect_Player.bottom
				|| enemy[i].Pos.y > vecPosPlayer.y + rcRect_Player.right
				|| enemy[i].Pos.y + rcRect_Enemy.right < vecPosPlayer.y)
			{

			}
			//충돌한경우
			else
			{
				if (enemy[i].Visible == TRUE)
				{
					score++;
				}
				enemy[i].Visible = FALSE;
			}
		}
	}
	//아이템 충돌처리
	if (HP_UP.Visible == TRUE)
	{
		if (vecPosPlayer.x > HP_UP.Pos.x + rcRect_Item.bottom
			|| vecPosPlayer.x + rcRect_Player.bottom < HP_UP.Pos.x
			|| vecPosPlayer.y > HP_UP.Pos.y + rcRect_Item.right
			|| vecPosPlayer.y + rcRect_Item.right < HP_UP.Pos.y)
		{

		}
		else
		{
			if (HP_UP.Visible == TRUE)
			{
				p_hp++;
			}
			HP_UP.Visible = FALSE;
		}
	}
	if (Speed_up.Visible == TRUE)
	{
		if (vecPosPlayer.x > Speed_up.Pos.x + rcRect_Item.bottom
			|| vecPosPlayer.x + rcRect_Player.bottom < Speed_up.Pos.x
			|| vecPosPlayer.y > Speed_up.Pos.y + rcRect_Item.right
			|| vecPosPlayer.y + rcRect_Item.right < Speed_up.Pos.y)
		{

		}
		else
		{
			if (Speed_up.Visible == TRUE)
			{
				Arrow[count_Arrow].Pos.y -= 15.0f;
				Bullet[count_Bullet].Pos.y -= 15.0f;
			}
			Speed_up.Visible = FALSE;
		}
	}
	//=================================================================
	//플레이어 무기 설정(p1)
	if (currentPlayer == Player1)
	{
		arrowFireTime += 2.0f;

		if (arrowFireTime > 10)
		{
			arrowFireTime = 0;

			Arrow[count_Arrow].Visible = true;
			Arrow[count_Arrow].Pos.x = vecPosPlayer.x + 64;
			Arrow[count_Arrow].Pos.y = vecPosPlayer.y - 20.0f;

			count_Arrow++;

			if (count_Arrow == 100)
			{
				count_Arrow = 0;
			}
		}

		for (int i = 0; i < 100; i++)
		{
			if (Arrow[i].Visible)
			{
				Arrow[i].Pos.y -= 10.0f;
			}
		}

		if (Arrow[count_Arrow].Pos.y + 125 <= 0.0f)
		{
			Arrow[count_Arrow].Visible = FALSE;
		}
	}
	//=========================================================
	//플레이어 무기 설정(p2)
	if (currentPlayer == Player2)
	{
		bulletFireTime += 2.0f;

		if (bulletFireTime > 10)
		{
			bulletFireTime = 0;

			Bullet[count_Bullet].Visible = true;
			Bullet[count_Bullet].Pos.x = vecPosPlayer.x + 64;
			Bullet[count_Bullet].Pos.y = vecPosPlayer.y - 20.0f;

			count_Bullet++;

			if (count_Bullet == 100)
			{
				count_Bullet = 0;
			}
		}

		for (int i = 0; i < 100; i++)
		{
			if (Bullet[i].Visible)
			{
				Bullet[i].Pos.y -= 10.0f;
			}
		}

		if (Bullet[count_Bullet].Pos.y + 125 <= 0.0f)
		{
			Bullet[count_Bullet].Visible = FALSE;
		}
	}
	//=================================================================
	//체력회복 아이템
	count_hp += 10;
	if (HP_UP.Visible == FALSE)
	{
		if (count_hp > counthpmax)
		{
			count_hp = 0;
			counthpmax += 5000;
			check++;
			HP_UP.Visible = TRUE;

			HP_UP.Pos.y = 0.0f;
			float x = (float)(rand() % 600 + 100);
			HP_UP.Pos.x = x;
		}
	}
	if (HP_UP.Visible == TRUE)
	{
		HP_UP.Pos.y += 20.0f;
	}
	if (HP_UP.Pos.y > 600.0f)
	{
		HP_UP.Visible = FALSE;
	}
	//공속 업그레이드 아이템
	count_speedup += 3;
	if (Speed_up.Visible == FALSE)
	{
		if (count_speedup > countspeedmax)
		{
			count_speedup = 0;
			countspeedmax += 5000;
			check++;

			Speed_up.Visible = TRUE;

			Speed_up.Pos.y = 0.0f;
			float x = (float)(rand() % 600 + 100);
			Speed_up.Pos.x = x;
		}
	}
	if (Speed_up.Visible == TRUE)
	{
		Speed_up.Pos.y += 18.5f;
	}
	if (Speed_up.Pos.y > 600.0f)
	{
		Speed_up.Visible = FALSE;
	}
	//=================================================================

	//플레이어 변경
	if (score < 45)
	{
		currentPlayer = Player1;

	}
	else if (45< score < 90)
	{
		currentPlayer = Player2;

		for (int i = 0; i < 100; i++)
		{
			Arrow[i].Pos.x = 1024.0f;
			Arrow[i].Pos.y = -1448.0f;
			Arrow[i].Visible = FALSE;
		}
		
	}
	if (90 < score)
	{
		currentPlayer = Player3;
		
		for (int i = 0; i < 100; i++)
		{
			Bullet[i].Pos.x = 1024.0f;
			Bullet[i].Pos.y = -1448.0f;
			Bullet[i].Visible = FALSE;
		}
	}
	if (score == 150)
	{
		currentScreen = RING_SCREEN;
		for (int i = 0; i < 10; i++)
		{
			
		}
	}
}

void Game2Update()
{
	//화면 스크롤
	vecPosGameBack_s2_1.y += 1.0f;
	vecPosGameBack_s2_2.y += 1.0f;
	if (vecPosGameBack_s2_1.y > 600)
	{
		vecPosGameBack_s2_1.y -= 1200.0f;
	}
	if (vecPosGameBack_s2_2.y > 600)
	{
		vecPosGameBack_s2_2.y -= 1200.0f;
	}
	//=================================================
	//거북선
	if (GetAsyncKeyState(VK_LEFT))
	{
		vecPosShip.x -= 1.5f;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		vecPosShip.x += 1.5f;
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		vecPosShip.y -= 1.5f;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		vecPosShip.y += 1.5f;
	}
	if (vecPosShip.y < 300.0)
	{
		vecPosShip.y = 300.0f;
	}
	if (vecPosShip.y > 600 - 150)
	{
		vecPosShip.y = 600 - 150;
	}
	if (vecPosShip.x < 100)
	{
		vecPosShip.x = 100.0f;
	}
	if (vecPosShip.x > 700-80)
	{
		vecPosShip.x = 700 - 80;
	}
	if (p_hp < 1)
	{
		currentScreen = DIE_SCREEN;
	}
	//=====================================================================
	//적 총알
	count_eBullet += 1.5;
	if (count_eBullet > 50)
	{
		count_eBullet = 0;
		check++;

		e_Bullet[e_bullet_count].Visible = TRUE;
		e_Bullet[e_bullet_count].Pos.y = 30.0f;
		float x = (float)(rand() % 600 + 100);
		e_Bullet[e_bullet_count].Pos.x = x;

		e_bullet_count++;

		if (e_bullet_count == 50)
		{
			e_bullet_count = 0;
		}

		for (int i = 0; i < 50; i++)
		{
			if (e_Bullet[i].Visible == TRUE)
			{
				e_Bullet[i].Pos.y += 70.0f;
			}
			else if (e_Bullet[i].Pos.y > vecPosShip.y + 30)
			{
				e_Bullet[i].Visible = FALSE;
			}
		}
	}
	//=========================================================================
	//점수
	if (score > 55000)
	{
		for (int i = 0; i < 50; i++)
		{
			e_Bullet[i].Visible = FALSE;
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			PlaySound("Wavs/Electro_1.wav", NULL, SND_ASYNC);
			Bullet2.Visible = TRUE;
		}
		vecPosShip.x = 1024.0f;
		vecPosShip.y = 2345.0f;
	}
	else
	{
		for (int i = 0; i < 50; i++)
		{
			if (e_Bullet[i].Visible == TRUE)
			{
				//충돌 x
				if (e_Bullet[i].Pos.x + rcRect_eBullet.bottom - 5 < vecPosShip.x + 5
					|| e_Bullet[i].Pos.x + 5 > vecPosShip.x + rcRect_Ship.bottom - 5
					|| e_Bullet[i].Pos.y + 20 > vecPosShip.y + rcRect_Ship.right - 20
					|| e_Bullet[i].Pos.y + rcRect_eBullet.right - 20 < vecPosShip.y + 20)
				{
					score++;
				}
				//충돌한경우
				else
				{
					if (e_Bullet[i].Visible == TRUE)
					{
						p_hp--;
					}
					e_Bullet[i].Visible = FALSE;
				}
			}
		}
	}
	//총알 발사
	if (Bullet2.Visible == TRUE)
	{
		vecPosBullet2.y -= 5.0f;
	}
	if (vecPosBullet2.y < -200)
	{
		currentScreen = ENDING_SCREEN;
		PlaySound("Wavs/MusicMono.wav", NULL, SND_ASYNC);

	}
}

void DieUpdate()
{

}

void RingUpdate()
{
	if ((beforeClick == true) && (currentClick == false))
	{
		currentScreen = GAME_SCREEN2;
		PlaySound("Wavs/HipHoppy_1.wav", NULL, SND_ASYNC);
	}
}

void EndingUpdate()
{
}

void Update()
{
	switch (currentScreen)
	{
		case INTRO_SCREEN:
			IntroUpdate();
			break;
		case MENU_SCREEN:
			MenuUpdate();
			break;
		case INFORM_SCREEN:
			InformUpdate();
			break;
		case GAME_SCREEN1:
			GameUpdate();
			break;
		case RING_SCREEN:
			RingUpdate();
			break;
		case DIE_SCREEN:
			DieUpdate();
			break;
		case GAME_SCREEN2:
			Game2Update();
			break;
		case ENDING_SCREEN:
			EndingUpdate();
			break;
	}

	beforeButton = currentButton;
	beforeClick = currentClick;
}

void IntroRender()
{
	g_pSprite->Draw(g_pIntro, &rcRect_Back, &vecCenter, &vecPosBack, 0xfffffffff );
}

void MenuRender()
{
	g_pSprite->Draw(g_pMenu, &rcRect_Back, &vecCenter, &vecPosBack, 0xfffffffff);
}

void InformRender()
{
	g_pSprite->Draw(g_pMenu, &rcRect_Back, &vecCenter, &vecPosBack, 0xfffffffff);
	g_pSprite->Draw(g_pInform, &rcRect_Tuto, &vecCenter, &vecPosTuto, 0xfffffffff);
}

void RingRender()
{
	g_pSprite->Draw(g_pRing, &rcRect_Back, &vecCenter, &vecPosBack, 0xfffffffff);
}

void DieRender()
{
	g_pSprite->Draw(g_pDie, &rcRect_Back, &vecCenter, &vecPosBack, 0xfffffffff);
}

void GameRender()
{
	g_pSprite->Draw(g_pStage_s1_1, &rcRect_Back, &vecCenter, &vecPosGameBack_s1_1, 0xfffffffff);
	g_pSprite->Draw(g_pStage_s1_2, &rcRect_Back, &vecCenter, &vecPosGameBack_s1_2, 0xfffffffff);
	g_pSprite->Draw(g_pStage_s1_3, &rcRect_Back, &vecCenter, &vecPosGameBack_s1_3, 0xfffffffff);
	
	sprintf(score_string, "점수 : %3d \n", score);
	sprintf(HP_string, "체력 : %3d \n", p_hp);
	RECT rt_score = { 0, 50, 0, 0 };
	RECT rt_hp = { 0, 20, 0, 0 };
	Font->DrawTextA(g_pSprite, score_string, -1, &rt_score, DT_NOCLIP, D3DCOLOR_XRGB(0, 0, 0));
	Font->DrawTextA(g_pSprite, HP_string, -1, &rt_hp, DT_NOCLIP, D3DCOLOR_XRGB(0, 0, 0));

	if (currentPlayer == Player1)
	{
		g_pSprite->Draw(g_pPlayer1, &rcRect_Player, &vecCenter, &vecPosPlayer, 0xfffffffff);
	}
	else if (currentPlayer == Player2)
	{
		g_pSprite->Draw(g_pPlayer2, &rcRect_Player, &vecCenter, &vecPosPlayer, 0xfffffffff);
	}
	else if (currentPlayer == Player3)
	{
		g_pSprite->Draw(g_pPlayer3, &rcRect_Player, &vecCenter, &vecPosPlayer, 0xfffffffff);
	}
	for (int i = 0; i < 100; ++i)
	{
		if (enemy[i].Visible == TRUE)
		{
			g_pSprite->Draw(g_pEnemy, &rcRect_Enemy, &vecCenter, &enemy[i].Pos, 0xfffffffff);
		}
	}
	for (int i = 0; i < 100; i++)
	{
		if (Arrow[i].Visible == TRUE)
		{
			g_pSprite->Draw(g_pArrow, &rcRect_Arrow, &vecCenter, &Arrow[i].Pos, 0xfffffffff);

		}
	}
	for (int i = 0; i < 100; i++)
	{
		if (Bullet[i].Visible == TRUE)
		{
			g_pSprite->Draw(g_pBullet, &rcRect_Bullet, &vecCenter, &Bullet[i].Pos, 0xfffffffff);
		}
	}
	if (Speed_up.Visible == TRUE)
	{
		g_pSprite->Draw(g_pItem_up, &rcRect_Item, &vecCenter, &Speed_up.Pos, 0xfffffffff);
	}
	if (HP_UP.Visible == TRUE)
	{
		g_pSprite->Draw(g_pItem_HP_UP, &rcRect_Item, &vecCenter, &HP_UP.Pos, 0xfffffffff);
	}
	if (score == 10)
	{
		g_pSprite->Draw(g_pState1, &rcRect_State, &vecCenter, &vecPosState, 0xfffffffff);
	}
	if (score == 20)
	{
		g_pSprite->Draw(g_pState2, &rcRect_State, &vecCenter, &vecPosState, 0xfffffffff);
	}
	if (score == 30)
	{
		g_pSprite->Draw(g_pState3, &rcRect_State, &vecCenter, &vecPosState, 0xfffffffff);
	}
	if (score == 40)
	{
		g_pSprite->Draw(g_pState4, &rcRect_State, &vecCenter, &vecPosState, 0xfffffffff);

	}
	if (score == 50)
	{
		g_pSprite->Draw(g_pState5, &rcRect_State, &vecCenter, &vecPosState, 0xfffffffff);
	}
	if (score == 65)
	{
		g_pSprite->Draw(g_pState6, &rcRect_State, &vecCenter, &vecPosState, 0xfffffffff);
	}
	if (score == 80)
	{
		g_pSprite->Draw(g_pState7, &rcRect_State, &vecCenter, &vecPosState, 0xfffffffff);
	}
	if (score == 95)
	{
		g_pSprite->Draw(g_pState8, &rcRect_State, &vecCenter, &vecPosState, 0xfffffffff);
	}
	if (score == 110)
	{
		g_pSprite->Draw(g_pState9, &rcRect_State, &vecCenter, &vecPosState, 0xfffffffff);
	}
	if (score == 130)
	{
		g_pSprite->Draw(g_pState10, &rcRect_State, &vecCenter, &vecPosState, 0xfffffffff);

	}
}

void Game2Render()
{
	g_pSprite->Draw(g_pStage_s2_1, &rcRect_Back, &vecCenter, &vecPosGameBack_s2_1, 0xfffffffff);
	g_pSprite->Draw(g_pStage_s2_2, &rcRect_Back, &vecCenter, &vecPosGameBack_s2_2, 0xfffffffff);

	sprintf(score_string, "점수 : %3d \n", score);
	sprintf(HP_string, "체력 : %3d \n", p_hp);
	RECT rt_score = { 0, 130, 0, 0 };
	RECT rt_hp = { 0, 100, 0, 0 };
	Font->DrawTextA(g_pSprite, score_string, -1, &rt_score, DT_NOCLIP, D3DCOLOR_XRGB(0, 0, 0));
	Font->DrawTextA(g_pSprite, HP_string, -1, &rt_hp, DT_NOCLIP, D3DCOLOR_XRGB(0, 0, 0));
	
	g_pSprite->Draw(g_pShip, &rcRect_Ship, &vecCenter, &vecPosShip, 0xfffffffff);
	
	count_Scene += 1;
	if (count_Scene > 80)
	{
		g_pSprite->Draw(g_pBoss2, &rcRect_Boss, &vecCenter, &vecPosBoss, 0xfffffffff);
		if (score > 55000)
		{
			g_pSprite->Draw(g_pBoss1, &rcRect_Boss, &vecCenter, &vecPosBoss, 0xfffffffff);
		}
		if (count_Scene > 160)
		{
			count_Scene = 0;
		}
	}
	else if (count_Scene <= 80)
	{
		g_pSprite->Draw(g_pBoss1, &rcRect_Boss, &vecCenter, &vecPosBoss, 0xfffffffff);
	}

	
	for (int i = 0; i < 100; i++)
	{
		if (e_Bullet[i].Visible == TRUE)
		{
			g_pSprite->Draw(g_pE_Bullet, &rcRect_eBullet, &vecCenter, &e_Bullet[i].Pos, 0xfffffffff);
		}
	}
	if (score > 54500)
	{
		g_pSprite->Draw(g_pSwan, &rcRect_Swan, &vecCenter, &vecPosSwan, 0xfffffffff);
	}
	if (Bullet2.Visible == TRUE)
	{
		g_pSprite->Draw(g_pBullet2, &rcRect_Bullet2, &vecCenter, &vecPosBullet2, 0xfffffffff);
	}
	if (vecPosBullet2.y < 100)
	{
		g_pSprite->Draw(g_pBomb, &rcRect_Bomb, &vecCenter, &vecPosBomb, 0xfffffffff);
	}
}

void EndingRender()
{
	g_pSprite->Draw(g_pEnding, &rcRect_Back, &vecCenter, &vecPosEnding, 0xfffffffff);
}

VOID Render()
{
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		switch (currentScreen)
		{
		case INTRO_SCREEN:
			IntroRender();
			break;
		case MENU_SCREEN:
			MenuRender();
			break;
		case INFORM_SCREEN:
			InformRender();
			break;
		case GAME_SCREEN1:
			GameRender();
			break;
		case RING_SCREEN:
			RingRender();
			break;
		case DIE_SCREEN:
			DieRender();
			break;
		case GAME_SCREEN2:
			Game2Render();
			break;
		case ENDING_SCREEN:
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
			Render();	//화면출력해주는데 값을 토대로 화면출력해줘
			Update();	//값을 업데이트.
		}
	}

	UnregisterClass("D3D Tutorial", g_wc.hInstance);
	return 0;
}