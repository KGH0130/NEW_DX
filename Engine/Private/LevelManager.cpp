#include "LevelManager.h"

LevelManager::LevelManager(GameInstance* Instance)
	: m_Instance(Instance)
{}

LevelManager::~LevelManager()
{
	SAFE_DELETE(m_CurLevel);
}

void LevelManager::OpenLevel(ILevel* Level)
{
	m_NextLevel = Level;
}

void LevelManager::SyncLevel()
{
	if(m_NextLevel == nullptr) return;

	if(m_CurLevel)
	{
		Reset();
		SAFE_DELETE(m_CurLevel);
	}

	m_CurLevel = m_NextLevel;
	m_NextLevel = nullptr;
	std::thread t1([&]
	{
		m_CurLevel->OnLoading(m_Instance);
	});
	// �ε� �����
	t1.join();
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
}

void LevelManager::Render()
{
	Render_Begin();
	m_Instance->Object.Render();
	Render_End();
}

void LevelManager::EndFrame()
{}

void LevelManager::Reset()
{
	m_Instance->Object.Clear();
	m_Instance->Resource.Clear();
}

void LevelManager::Render_Begin()
{
	m_Instance->Device->Clear(0, nullptr,
							  D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
							  D3DCOLOR(0xFF0000FF), 1.f, 0);
	m_Instance->Device->BeginScene();
}

void LevelManager::Render_End()
{
	m_Instance->Device->EndScene();
	m_Instance->Device->Present(nullptr, nullptr, nullptr, nullptr);
}
