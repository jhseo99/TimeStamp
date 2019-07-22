#include "DXUT.h"
#include "GaBase.h"


Track::Track()
{
}

Track::Track(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename)
{
	CreateTexture(pd3dDevice, filename);
	SetSection();
}

Track::~Track()
{
}

void Track::SetSection()
{
	SetVector(&vSection[0], 2503, 4735);
	SetVector(&vSection[1], 992, 3111);
	SetVector(&vSection[2], 992, 2402);
	SetVector(&vSection[3], 2503, 780);
	SetVector(&vSection[4], 9896, 780);
	SetVector(&vSection[5], 11308, 2402);
	SetVector(&vSection[6], 11308, 3111);
	SetVector(&vSection[7], 9896, 4735);
}
