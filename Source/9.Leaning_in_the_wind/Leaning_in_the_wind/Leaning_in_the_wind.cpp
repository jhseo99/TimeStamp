//--------------------------------------------------------------------------------------
// File: Leaning_in_the_wind.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "DXUT.h"
#include "resource.h"
#include "GaBase.h"

Intro* pIntro = new Intro;
Menu* pMenu = new Menu;
Stage* pStage = new Stage;
Ending* pEnding = new Ending;

RenderObject* pBlack = new RenderObject;
RenderObject* pSceneChange = new RenderObject;

//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext )
{
    // Typically want to skip back buffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    return true;
}


//--------------------------------------------------------------------------------------
// Before a device is created, modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
	pIntro->Create(pd3dDevice);
	pMenu->Create(pd3dDevice);
	pStage->Create(pd3dDevice);
	pEnding->Create(pd3dDevice);
	
	pBlack->CreateTexture(pd3dDevice, L"texture\\black.png");
	pBlack->SetRect(0, 800, 0, 600);
	pBlack->SetTranslate(0, 0);
	pBlack->SetPosition(0, 0, 0);
	pBlack->SetVisible(false);

	pSceneChange->CreateTexture(pd3dDevice, L"texture\\SceneChange.png");
	pSceneChange->SetRect(0, 800, 0, 600);
	pSceneChange->SetTranslate(0, 0);
	pSceneChange->SetPosition(0, 0, 0);
	pSceneChange->SetVisible(false);
	return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext )
{
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
	GATIMER()->Update();
	switch (SCENEMANAGER()->GetCurrentScene())
	{
	case SceneManager::SceneState::INTRO:
		pIntro->Update();
		break;
	case SceneManager::SceneState::MENU:
		pMenu->Update();
		break;
	case SceneManager::SceneState::STAGE:
		pStage->Update();
		break;
	case SceneManager::SceneState::ENDING:
		pEnding->Update();
		break;
	default:
		break;
	}
	if (SCENEMANAGER()->bSceneChange)
	{
		SCENEMANAGER()->fSceneAlpha -= 0.02f;
		pBlack->SetColor(1.0f, 1.0f, 1.0f, SCENEMANAGER()->fSceneAlpha);
		if (SCENEMANAGER()->fSceneAlpha <= 0.0f)
		{
			SCENEMANAGER()->bSceneChange = false;
		}
	}
	pBlack->SetVisible(SCENEMANAGER()->bSceneChange);
	pSceneChange->SetVisible(SCENEMANAGER()->bSceneChange);
	SCENEMANAGER()->bCurrentClick = SCENEMANAGER()->bBeforeClick;
}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D9 device
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    // Clear the render target and the zbuffer 
    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 ) );

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
		switch (SCENEMANAGER()->GetCurrentScene())
		{
		case SceneManager::SceneState::INTRO:
			pIntro->Render();
			break;
		case SceneManager::SceneState::MENU:
			pMenu->Render();
			break;
		case SceneManager::SceneState::STAGE:
			pStage->Render();
			break;
		case SceneManager::SceneState::ENDING:
			pEnding->Render();
			break;
		default:
			break;
		}
		pSceneChange->Render();
		pBlack->Render();

        V( pd3dDevice->EndScene() );
    }
}


//--------------------------------------------------------------------------------------
// Handle messages to the application 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		SCENEMANAGER()->bCurrentClick = true;
		break;
	case WM_LBUTTONUP:
		SCENEMANAGER()->bBeforeClick = false;
		break;
	default:
		break;
	}

    return 0;
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9ResetDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9CreateDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
}


//--------------------------------------------------------------------------------------
// Initialize everything and go into a render loop
//--------------------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // Set the callback functions
    DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackFrameMove( OnFrameMove );

    // TODO: Perform any application-level initialization here

    // Initialize DXUT and create the desired Win32 window and Direct3D device for the application
    DXUTInit( false, false ); // Parse the command line and show msgboxes
    DXUTSetHotkeyHandling( true, true, true );  // handle the default hotkeys
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen
    DXUTCreateWindow( L"Leaning_in_the_wind" );
    DXUTCreateDevice( false, 800, 600 );

    // Start the render loop
    DXUTMainLoop();

    // TODO: Perform any application-level cleanup here

    return DXUTGetExitCode();
}


