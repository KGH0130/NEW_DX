#include "CameraManager.h"

CameraManager::~CameraManager()
{
	SAFE_DELETE_VEC(m_Cameras);

	for(auto& [name, ptr] : m_CameraMap)
	{
		SAFE_DELETE(ptr);
	}
	m_CameraMap.clear();
	m_CloneMap.clear();
}

void CameraManager::Register(const std::string& Name, ICamera* Camera)
{
	auto iter = m_CameraMap.find(Name);
	assert(iter == m_CameraMap.end());
	m_CameraMap.emplace(Name, Camera);
}

ICamera* CameraManager::Init(const std::string& Name, IObject* Target)
{
	auto iter = m_CameraMap.find(Name);
	assert(iter != m_CameraMap.end());
	ICamera* newCamera = iter->second->Clone();
	m_CloneMap.emplace(Name, newCamera);
	newCamera->SetID(m_Cameras.size());
	newCamera->Initialize();
	newCamera->SetTarget(Target);
	return m_AddPending.emplace_back(newCamera);
}

ICamera* CameraManager::Get(const std::string& Name)
{
	auto iter = m_CloneMap.find(Name);
	assert(iter != m_CloneMap.end());
	return iter->second;
}

void CameraManager::Release(const ICamera* Camera)
{
	m_RemovePending.emplace_back(Camera->GetID());
}

void CameraManager::LateUpdate(float dt)
{
	for(auto& var : m_Cameras)
	{
		var->OnLateUpdate(dt);
	}
}

void CameraManager::Flush()
{
	AddPending();
	RemovePending();
}

void CameraManager::AddPending()
{
	if(m_AddPending.empty()) return;

	for(auto& var : m_AddPending)
	{
		m_Cameras.emplace_back(var);
	}
	m_AddPending.clear();
}

void CameraManager::RemovePending()
{
	if(m_RemovePending.empty()) return;

	for(auto& var : m_RemovePending)
	{
		auto& delCamera = m_Cameras[var];
		size_t last = m_Cameras.size() - 1;

		if(var != last)
		{
			auto& lastCamera = m_Cameras[last];
			m_Cameras[var] = lastCamera;
			lastCamera->SetID(var);
		}
		m_Cameras.pop_back();
		SAFE_DELETE(delCamera);
	}
	m_RemovePending.clear();
}