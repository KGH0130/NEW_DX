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
	m_NextLevel = Level;
	m_Load = Load;
}

void LevelManager::SyncLevel()
{
	if(m_NextLevel == nullptr) return;

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
		m_Load->Enter();
		while(!LoadingExit)
		{
			m_Load->Update();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		m_Load->Exit();
		SAFE_DELETE(m_Load);
	}

	Loding.join();
}

void LevelManager::FixedUpdate(float dt)
{
	m_Instance->Object.FixedUpdate(dt);
}

void LevelManager::Update(float dt)
{
	m_Instance->Input.Update();
	m_Instance->Object.Update(dt);
	m_Instance->Collider.Update();
	m_Instance->Collider.ProcessCollisions();
}

void LevelManager::LateUpdate(float dt)
{
	m_Instance->Object.LateUpdate(dt);
}

void LevelManager::Render()
{
	RenderEnter();
	m_Instance->Object.Render();
	//#ifdef _DEBUG
	m_Instance->Collider.Render(m_Instance->Device);
	//#endif
	RenderExit();
}

void LevelManager::EndFrame()
{
	m_Instance->Collider.Flush();
	m_Instance->Object.Flush();
}

void LevelManager::Reset()
{
	SAFE_DELETE(m_CurLevel);
	m_Instance->Collider.Clear();
	m_Instance->Object.Clear();
}

void LevelManager::RenderEnter()
{
	m_Instance->Device->Clear(0, nullptr,
							  D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
							  D3DCOLOR_ARGB(255, 32, 32, 32), 1.f, 0);
	m_Instance->Device->BeginScene();
}

void LevelManager::RenderExit()
{
	m_Instance->Device->EndScene();
	m_Instance->Device->Present(nullptr, nullptr, nullptr, nullptr);
}
