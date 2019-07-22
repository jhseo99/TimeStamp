#include "DXUT.h"
#include "GaBase.h"

Camera Camera::singleton;

Camera::Camera()
{
	Init();
}


Camera::~Camera()
{
}

void Camera::Init()
{
	vCameraPos.x = 0.0f;
	vCameraPos.y = 0.0f;
}