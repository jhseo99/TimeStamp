#pragma once

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib, "winmm.lib")

namespace GaBase
{
	enum TextureID
	{
		INTRO,
		MENU,
		CHOOSE,
		UI,
		GOAL,
		WIN,
		LOSE,
		STAGE1_BACK,
		STAGE2_BACK,
		STAGE3_BACK,
		LANDROVER,
		ENEMY,
		CAR1,
		CAR2,
		TRUCK,
		MINI_PLAYER,
		MINI_ENEMY,
		ENDING,
		WIND,
	};
}

#include <Windows.h>
#include <strsafe.h>
#include <stdlib.h>
#include <hash_map>
#include <time.h>

#include <d3d9.h>
#include <d3dx9.h>

using namespace std;

#include "Object.h"
#include "GameObject.h"
#include "LandRover.h"
#include "Enemy.h"
#include "Car.h"
#include "ObjectManager.h"
#include "GaTimer.h"
#include "GaApp.h"