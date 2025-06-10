#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class ILevel;
struct GameInstance;

class DLL LevelManager
{
public:
	LevelManager(GameInstance* Instance);
	~LevelManager();

public:
	void OpenLevel(ILevel* Level);
	void SyncLevel();

	void FixedUpdate(float dt);
	void Update(float dt);
	void LateUpdate(float dt);
	void Render();
	void EndFrame();

private:
	void RenderEnter();
	void RenderExit();
	void Reset();
private:
	ILevel* m_CurLevel = nullptr;
	ILevel* m_NextLevel = nullptr;

private:
	GameInstance* m_Instance = nullptr;
};
END