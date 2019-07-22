#pragma once

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9d.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

#define PI 3.141592

namespace GaBase
{
	enum TextureID
	{
		INTRO,
		BG_STAGE1_1,
		BG_STAGE1_2,
		BG_STAGE2_1,
		BG_STAGE2_2,
		STORM_1,
		STORM_2,
		PLAYER1,
		PLAYER2,
		MISSILE,
		DIRECTBULLET,
		AIMBULLET,
		NWAYBULLET,
		CIRCLEBULLET,
		AIMBULLET2,
		BOSSBULLET,
		RIDER,
		SOLDIER,
		BOMBER,
		WHEEL,
		BUZZARD,
		TANK,
		TRUCK,
		BOSS,
		HITEFFECT,
		EXPLOSION,
		BOMBEFFECT,
		BOSSEFFECT,
		GAUGEBAR,
		GAUGE,
		HPUP,
		GUN,
		UI,
		DIE,
		ENDING
	};
}

#include <tchar.h>
#include <Windows.h>
#include <strsafe.h>
#include <stdlib.h>
#include <hash_map>
#include <string>
#include <math.h>
#include <time.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

using namespace std;
using namespace stdext;

#include "GaTimer.h"
#include "Object.h"
#include "Screen.h"
#include "GaugeBar.h"
#include "Gauge.h"
#include "Item.h"
#include "Missile.h"
#include "Bullet.h"
#include "Effect.h"
#include "Enemy.h"
#include "Bomber.h"
#include "Wheel.h"
#include "Buzzard.h"
#include "Tank.h"
#include "Soldier.h"
#include "Rider.h"
#include "Truck.h"
#include "Boss.h"
#include "Player.h"
#include "GaKeyboard.h"
#include "GaMouse.h"
#include "GaInput.h"
#include "ObjectManager.h"
#include "GaApp.h"