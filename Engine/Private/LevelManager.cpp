#include "LevelManager.h"

LevelManager::LevelManager(GameInstance* Instance)
	: m_Instance(Instance)
{}

LevelManager::~LevelManager()
{
	SAFE_DELETE(m_Load);
	SAFE_DELETE(m_CurLevel);
}

void LevelManager::OpenLevel(ILevel* Level, ILoad* Load)
{
	SAFE_DELETE(m_Load);

	m_NextLevel = Level;
	m_Load = Load;
}

void LevelManager::SyncLevel()
{
	if(m_NextLevel == nullptr) return;

	SAFE_DELETE(m_CurLevel);
	Reset();

	m_CurLevel = m_NextLevel;
	m_NextLevel = nullptr;
	bool LoadingExit = false;

	std::thread Loding([&]
	{
		LoadingExit = m_CurLevel->OnLoading(m_Instance);
	});

	if(m_Load && !LoadingExit)
	{
		while(!LoadingExit)
		{
			m_Load->LOAD();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	Loding.join();
}

void LevelManager::FixedUpdate(float dt)
{
	m_Instance->Object.FixedUpdate(dt);
}

void LevelManager::Update(float dt)
{
	m_Instance->Object.Update(dt);
}

void LevelManager::LateUpdate(float dt)
{
	m_Instance->Object.LateUpdate(dt);
	m_Instance->Component.TransformUpdate();
}

void LevelManager::Render()
{
	RenderEnter();
	m_Instance->Object.Render();
	RenderExit();
}

void LevelManager::EndFrame()
{
	m_Instance->Component.Flush();
	m_Instance->Object.Flush();
}

void LevelManager::Reset()
{
	if(!m_CurLevel) return;

	m_Instance->Component.Clear();
	m_Instance->Object.Clear();
}

void LevelManager::RenderEnter()
{
	m_Instance->Device->Clear(0, nullptr,
							  D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
							  D3DCOLOR(0xFF0000FF), 1.f, 0);
	m_Instance->Device->BeginScene();
}

void LevelManager::RenderExit()
{
	m_Instance->Device->EndScene();
	m_Instance->Device->Present(nullptr, nullptr, nullptr, nullptr);
}
