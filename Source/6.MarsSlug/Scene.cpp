#include "DXUT.h"
#include "Scene.h"


Scene::Scene()
{
	InitScene();
}


Scene::~Scene()
{
}

void Scene::InitScene()
{
	bSceneEnd = false;
}

void Scene::CreateScene(LPDIRECT3DDEVICE9 pd3dDevice)
{

}

void Scene::Update()
{

}

void Scene::Render(LPD3DXSPRITE pSprite)
{

}

void Scene::KeyProc()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		bSceneEnd = true;
	}
}

void Scene::MouseProc(UINT nMsg)
{
	switch (nMsg)
	{
	case WM_LBUTTONDOWN:
		bSceneEnd = true;
		break;
	default:
		break;
	}
}