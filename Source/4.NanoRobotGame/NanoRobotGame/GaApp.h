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

	enum GameMode{ INTRO, MENU, STAGE1, STAGE2, ENDING, DIE};

private:
	GaApp();

	static GaApp singleton;

	HWND hWnd;
	HINSTANCE hInstance;
	DWORD nBeforeFrame;

	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	LPD3DXSPRITE m_pSprite;

	ID3DXFont* Font;

	GameMode gamemode;

	static bool bClick;

public:
	LPDIRECT3DDEVICE9 GetDevice() { return m_pd3dDevice; }

	GameMode GetGameMode() { return gamemode; }
	void SetGameMode(GameMode mode) { gamemode = mode; }

	LPD3DXSPRITE GetSprite() { return m_pSprite; }

	ID3DXFont* GetFont() { return Font; }

	static bool GetClick() { return bClick; }

private:
	static int nScreenWidth;
	static int nScreenHeight;
};

#define GAAPP() GaApp::Instance()