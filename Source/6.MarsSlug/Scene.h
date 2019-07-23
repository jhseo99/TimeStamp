#pragma once
class Scene
{
public:
	Scene();
	~Scene();

public:
	bool bSceneEnd;

protected:
	void InitScene();

public:
	virtual void CreateScene(LPDIRECT3DDEVICE9 pd3dDevice);
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void KeyProc();
	virtual void MouseProc(UINT nMsg);
};

