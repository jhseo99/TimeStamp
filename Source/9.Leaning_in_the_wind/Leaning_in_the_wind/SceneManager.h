#pragma once
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	static SceneManager* Instance() { return &singleton; }

	enum SceneState{INTRO, MENU, STAGE, ENDING};

private:
	static SceneManager singleton;

	SceneState CurrentScene;

public:
	bool bSceneChange;
	float fSceneAlpha;

	bool bCurrentClick;
	bool bBeforeClick;

public:
	void Create();
	
	SceneState GetCurrentScene() { return CurrentScene; }
	void SetCurrentScene(SceneState scene) { CurrentScene = scene; SceneChange(); }
	void SceneChange() { bSceneChange = true; fSceneAlpha = 1.0f; }
};

#define SCENEMANAGER() SceneManager::Instance()