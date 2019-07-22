#pragma once
class Camera
{
public:
	Camera();
	~Camera();

	static Camera* Instance() { return &singleton; }

private:
	static Camera singleton;

	D3DXVECTOR2 vCameraPos;

public:
	void Init();

	D3DXVECTOR2* GetCameraPos() { return &vCameraPos; }
	void SetCameraPos(D3DXVECTOR2 pos) { vCameraPos = -pos; }
};

#define CAMERA() Camera::Instance()