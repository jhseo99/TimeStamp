#pragma once

class GaApp
{
public:
	~GaApp();

	static GaApp* Instance() { return &singleton; }
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitD3D();
	void Render();
	int Run();
	void Release();

	enum GameMode{ INTRO, MENU, CHOOSE, STAGE1, STAGE2, STAGE3, ENDING};

private:
	GaApp();

	static GaApp singleton;

	static GameMode gamemode;

	HWND hWnd;
	HINSTANCE hInstance;
	DWORD nBeforeLastFrame;

	LPDIRECT3D9 pD3D;
	LPDIRECT3DDEVICE9 pd3dDevice;
	LPD3DXSPRITE pSprite;

	ID3DXFont* Font;

	static bool bBeforeClick;
	static bool bCurrentClick;

public:
	GameMode GetGameMode() { return gamemode; }
	void SetGameMode(GameMode mode) { gamemode = mode; }

	LPDIRECT3DDEVICE9 GetDevice() { return pd3dDevice; }
	LPD3DXSPRITE GetSprite() { return pSprite; }
	ID3DXFont* GetFont() { return Font; }

	static bool GetClick() { return bCurrentClick; }

private:
	static int nScreenWidth;
	static int nScreenHeight;
};

#define GAAPP() GaApp::Instance()