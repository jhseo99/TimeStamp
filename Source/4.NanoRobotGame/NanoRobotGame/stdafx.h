#pragma once

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

namespace GaBase
{
	enum TextureID
	{
		INTRO,
		GRAPH,
		SMOKE,
		BUTTON,
		UI,
		HEART,
		HP,
		PLAYER,
		MISSILE,
		STAGE1,
		STAGE2,
		RED_ENEMY,
		VIRUS,
		WHITE_ENEMY,
		BACTERIA,
		CANCER1,
		CANCER2,
		ENDING,
		DIE,
		TITLE,
	};
}

#include <Windows.h>
#include <strsafe.h>
#include <stdlib.h>
#include <hash_map>
#include <time.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <dsound.h>

using namespace std;

#include "GaTimer.h"
#include "Object.h"
#include "GameObject.h"
#include "Missile.h"
#include "Player.h"
#include "Enemy.h"
#include "RedEnemy.h"
#include "Virus.h"
#include "WhiteEnemy.h"
#include "Bacteria.h"
#include "Cancer.h"
#include "Sound.h"
#include "ObjectManager.h"
#include "GaApp.h"