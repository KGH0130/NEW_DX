#include "ObjectManager.h"

ObjectManager::~ObjectManager()
{
	Clear();
}

void ObjectManager::RegisterObject(const std::string& Name, IObject* Object)
{
	auto iter = m_ObjectMap.find(Name);
	if(iter != m_ObjectMap.end())
	{
		SAFE_DELETE(Object);
		assert(false);
	}
	m_ObjectMap.emplace(Name, Object);
}

IObject* ObjectManager::AddObject(RENDER_TYPE Type, const std::string& Name)
{
	m_AddPending.emplace_back(Type, Name);

	//auto iter = m_ObjectMap.find(Name);
	//assert(iter != m_ObjectMap.end());
	//auto* newObj = iter->second->Clone();
	//
	//if(Type == RENDER_TYPE::NONE)
	//{
	//	newObj->SetInfo(m_Objects.size(), Type, INVALID);
	//}
	//else
	//{
	//	auto& renderer = m_Render[static_cast<size_t>(Type)];
	//	newObj->SetInfo(m_Objects.size(), Type, renderer.size());
	//	renderer.emplace_back(newObj);
	//}
	//
	//m_Objects.emplace_back(newObj);
	//newObj->Initialize();
	//return newObj;
}

void ObjectManager::RemoveObject(const ObjectInfo& Info)
{
	m_DeletePending.emplace_back(Info);
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
	SAFE_DELETE_VEC(m_Objects);

	for(auto& var : m_Render)
	{
		var.clear();
	}

	for(auto& [name, Ptr] : m_ObjectMap)
	{
		SAFE_DELETE(Ptr);
	}
}