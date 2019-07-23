#include "DXUT.h"
#include "GaBase.h"


Beach::Beach()
{
}

Beach::Beach(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename)
{
	CreateTexture(pd3dDevice, filename);
	SetSection();
}

Beach::~Beach()
{
}

void Beach::SetSection()
{
	SetVector(&vSection[0], 1841, 937);
	SetVector(&vSection[1], 8145, 937);
	SetVector(&vSection[2], 9051, 1843);
	SetVector(&vSection[3], 9051, 5201);
	SetVector(&vSection[4], 8145, 6107);
	SetVector(&vSection[5], 4781, 6114);
	SetVector(&vSection[6], 889, 3086);
	SetVector(&vSection[7], 897, 1843);
}
