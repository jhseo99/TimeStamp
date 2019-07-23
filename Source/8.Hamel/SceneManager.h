#pragma once
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	static SceneManager* Instance() { return &singleton; }

	enum Scene{INTRO, MENU, STAGE, ENDING};

public:
	static SceneManager singleton;

	Scene m_enCurrentScene;

public:
	void Init();
};

#define SCENEMANAGER() SceneManager::Instance()