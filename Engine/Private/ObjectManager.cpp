#include "ObjectManager.h"

ObjectManager::~ObjectManager()
{
	Clear();
}

void ObjectManager::RegisterObject(const std::string& Name, IObject* Ptr)
{
	auto iter = m_ObjectMap.find(Name);
	assert(iter == m_ObjectMap.end());
	m_ObjectMap.emplace(Name, Ptr);
}

IObject* ObjectManager::AddObject(RENDERTYPE Type, const std::string& Name)
{
	auto iter = m_ObjectMap.find(Name);
	assert(iter != m_ObjectMap.end());
	IObject* newObj = iter->second;
	if(Type != RENDERTYPE::NONE)
		m_Render[static_cast<size_t>(Type)].emplace_back(newObj);
	m_Objects.emplace_back(newObj);
	return newObj;
}

void ObjectManager::FixedUpdate(float dt)
{
	for(auto& var : m_Objects)
	{
		var->FixedUpdate(dt);
	}
}
void ObjectManager::Update(float dt)
{
	for(auto& var : m_Objects)
	{
		var->Update(dt);
	}
}
void ObjectManager::LateUpdate(float dt)
{
	for(auto& var : m_Objects)
	{
		var->LateUpdate(dt);
	}
}
void ObjectManager::Render()
{
	for(auto& var : m_Render)
	{
		for(auto& dst : var)
		{
			dst->OnRender();
		}
	}
}

void ObjectManager::Clear()
{
	for(auto& var : m_Objects)
	{
		var->Free();
		SAFE_DELETE(var);
	}
	m_Objects.clear();

	for(auto& var : m_Render)
	{
		var.clear();
	}

	for(auto& [name, Ptr] : m_ObjectMap)
	{
		Ptr->Free();
		SAFE_DELETE(Ptr);
	}
}