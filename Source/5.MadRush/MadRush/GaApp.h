#pragma once

class GaApp
{
public:
	~GaApp(void);

	static GaApp* Instance() { return &singleton; }
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Init(HINSTANCE hInstance, LPSTR lpszParam, int nCmdShow);
	HRESULT InitD3D();
	void Render();
	void Release();
	int Run();

	static enum GameMode{ INTRO, GAME1, GAME2, DIE, ENDING };

private:
	GaApp(void);

	static GaApp singleton;

	HWND hWnd;
	HINSTANCE hInstance;
	LPCTSTR lpszClass;
	DWORD nBeforeFrame;

	LPDIRECT3D9 pD3D;
	LPDIRECT3DDEVICE9 pd3dDevice;
	LPD3DXSPRITE pSprite;

	ID3DXFont* Font;

	GameMode mode;
	
public:
	LPDIRECT3DDEVICE9 GetDevice() { return pd3dDevice; }

	LPD3DXSPRITE GetSprite() { return pSprite; }

	ID3DXFont* GetFont() { return Font; }

	GameMode GetGameMode() { return mode; }
	void SetGameMode(GameMode _mode) { mode = _mode; }

public:
	static int nScreenWidth;
	static int nScreenHeight;
};

#define GAAPP() GaApp::Instance()