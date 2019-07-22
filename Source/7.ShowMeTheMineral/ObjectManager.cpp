#include "DXUT.h"
#include "ObjectManager.h"

ObjectManager ObjectManager::singleton;

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::Create(LPDIRECT3DDEVICE9 pd3dDevice)
{
	this->pd3dDevice = pd3dDevice;
	D3DXCreateSprite(pd3dDevice, &pSprite);

	Score = 0;

	FirstScore = 0;
	SecondScore = 0;
	ThirdScore = 0;

	for (int i = 0; i < 5; i++)
	{
		FirstPlayer[i] = NULL;
		SecondPlayer[i] = NULL;
		ThirdPlayer[i] = NULL;
		CurrentPlayer[i] = NULL;
	}

	D3DXCreateFont( pd3dDevice, 75, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
					L"System", &pFontTime);
	D3DXCreateFont( pd3dDevice, 30, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
					L"System", &pFontStr);

	LoadTexture(L"texture\\stage1Water.png", GaBase::TextureID::STAGE1_WATER);
	LoadTexture(L"texture\\stage1_1_1.png", GaBase::TextureID::STAGE1_L1_1);
	LoadTexture(L"texture\\stage1_1_2.png", GaBase::TextureID::STAGE1_L1_2);
	LoadTexture(L"texture\\stage1_2_1.png", GaBase::TextureID::STAGE1_L2_1);
	LoadTexture(L"texture\\stage1_2_2.png", GaBase::TextureID::STAGE1_L2_2);
	LoadTexture(L"texture\\stage1_3_1.png", GaBase::TextureID::STAGE1_L3_1);
	LoadTexture(L"texture\\stage1_3_2.png", GaBase::TextureID::STAGE1_L3_2);
	LoadTexture(L"texture\\Player.png", GaBase::TextureID::PLAYER);
	LoadTexture(L"texture\\PlayerBullet.png", GaBase::TextureID::PLAYER_BULLET);
	LoadTexture(L"texture\\PlayerMissile.png", GaBase::TextureID::PLAYER_MISSILE);
	LoadTexture(L"texture\\PlayerAimMissile.png", GaBase::TextureID::PLAYER_MISSILE_AIM);
	LoadTexture(L"texture\\PlayerFire.png", GaBase::TextureID::PLAYER_FIRE);
	LoadTexture(L"texture\\PlayerBomb.png", GaBase::TextureID::PLAYER_BOMB);
	LoadTexture(L"texture\\ui.png", GaBase::TextureID::UI);
	LoadTexture(L"texture\\PlayerHp.png", GaBase::TextureID::PLAYER_HP);
	LoadTexture(L"texture\\PlayerHit.png", GaBase::TextureID::PLAYER_HIT);
	LoadTexture(L"texture\\StoneWave.png", GaBase::TextureID::STONE_WAVE);
	LoadTexture(L"texture\\StoneWaveFree.png", GaBase::TextureID::STONE_WAVE_FREE);
	LoadTexture(L"texture\\StoneHorn.png", GaBase::TextureID::STONE_HORN);
	LoadTexture(L"texture\\StoneHole.png", GaBase::TextureID::STONE_HOLE);
	LoadTexture(L"texture\\Matt.png", GaBase::TextureID::MATT);
	LoadTexture(L"texture\\James.png", GaBase::TextureID::JAMES);
	LoadTexture(L"texture\\JamesBullet.png", GaBase::TextureID::JAMES_BULLET);
	LoadTexture(L"texture\\BombEffect1.png", GaBase::TextureID::BOMB_EFFECT1);
	LoadTexture(L"texture\\Rock.png", GaBase::TextureID::ROCK);
	LoadTexture(L"texture\\Seaweed.png", GaBase::TextureID::SEAWEED);
	LoadTexture(L"texture\\Boris.png", GaBase::TextureID::BORIS);
	LoadTexture(L"texture\\BorisBullet.png", GaBase::TextureID::BORIS_BULLET);
	LoadTexture(L"texture\\MiddleBossBomb1.png", GaBase::TextureID::MIDDLE_BOSS_BOMB1);
	LoadTexture(L"texture\\BossHpBar.png", GaBase::TextureID::BOSS_HP_BAR);
	LoadTexture(L"texture\\BossHp.png", GaBase::TextureID::BOSS_HP);
	LoadTexture(L"texture\\cedric.png", GaBase::TextureID::CEDRIC);
	LoadTexture(L"texture\\cedricbullet1.png", GaBase::TextureID::CEDRIC_BULLET1);
	LoadTexture(L"texture\\cedricbullet2.png", GaBase::TextureID::CEDRIC_BULLET2);
	LoadTexture(L"texture\\bossBomb1.png", GaBase::TextureID::BOSS_BOMB1);
	LoadTexture(L"texture\\ItemHp.png", GaBase::TextureID::ITEM_HP);
	LoadTexture(L"texture\\ItemMissile.png", GaBase::TextureID::ITEM_MISSILE);
	LoadTexture(L"texture\\ItemMissileThree.png", GaBase::TextureID::ITEM_MISSILE_THREE);
	LoadTexture(L"texture\\ItemAimMissile.png", GaBase::TextureID::ITEM_AIM_MISSILE);
	LoadTexture(L"texture\\ItemBomb.png", GaBase::TextureID::ITEM_BOMB);
	LoadTexture(L"texture\\ItemGun.png", GaBase::TextureID::ITEM_GUN);
	LoadTexture(L"texture\\ItemSpeed.png", GaBase::TextureID::ITEM_SPEED);
	LoadTexture(L"texture\\ItemAddon.png", GaBase::TextureID::ITEM_ADDON);
	LoadTexture(L"texture\\Addon.png", GaBase::TextureID::ADD_ON);
	LoadTexture(L"texture\\AddonBullet.png", GaBase::TextureID::ADD_ON_BULLET);
	LoadTexture(L"texture\\John.png", GaBase::TextureID::JOHN);
	LoadTexture(L"texture\\JohnBullet.png", GaBase::TextureID::JOHN_BULLET);
	LoadTexture(L"texture\\BombEffect2.png", GaBase::TextureID::BOMB_EFFECT2);
	LoadTexture(L"texture\\Chris.png", GaBase::TextureID::CHRIS);
	LoadTexture(L"texture\\ChrisBullet.png", GaBase::TextureID::CHRIS_BULLET);
	LoadTexture(L"texture\\Richard.png", GaBase::TextureID::RICHARD);
	LoadTexture(L"texture\\Lazer.png", GaBase::TextureID::LAZER);
	LoadTexture(L"texture\\Herrald.png", GaBase::TextureID::HERRALD);
	LoadTexture(L"texture\\HerraldBullet1.png", GaBase::TextureID::HERRALD_BULLET1);
	LoadTexture(L"texture\\HerraldBullet2.png", GaBase::TextureID::HERRALD_BULLET2);
	LoadTexture(L"texture\\Ending.png", GaBase::TextureID::ENDING);
	LoadTexture(L"texture\\Intro.png", GaBase::TextureID::INTRO);
	LoadTexture(L"texture\\Menu.png", GaBase::TextureID::MENU);

	currentScene = SceneState::INTRO;
}

void ObjectManager::LoadTexture(TCHAR* filename, DWORD id)
{
	D3DXCreateTextureFromFileEx(pd3dDevice,
		filename,
		D3DX_DEFAULT, D3DX_DEFAULT,
		1,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		NULL,
		NULL,
		NULL,
		&pTexture);

	TextureMap.insert(TEXMAP_PAIR(id, pTexture));
}

LPDIRECT3DTEXTURE9 ObjectManager::GetTexture(DWORD id)
{
	TEXMAP_ITER iter;

	iter = TextureMap.find(id);

	if (iter == TextureMap.end())
	{
		return NULL;
	}

	return iter->second;
}