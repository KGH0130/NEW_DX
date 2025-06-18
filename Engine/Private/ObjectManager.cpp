#include "ObjectManager.h"

ObjectManager::~ObjectManager()
{
	Clear();
	SAFE_DELETE_VEC(m_Objects[static_cast<size_t>(CREATE_TYPE::STATIC)]);
}

void ObjectManager::Register(const std::string& Name, IObject* Object, CREATE_TYPE Type)
{
	if(m_ObjectMap.count(Name))
	{
		SAFE_DELETE(Object);
		assert(false);
	}
	m_ObjectMap.emplace(Name, std::pair{ Object, Type });
}

IObject* ObjectManager::Init(RENDER_TYPE Type, const std::string& Name, Vector3 Pos)
{
	auto iter = m_ObjectMap.find(Name);
	assert(iter != m_ObjectMap.end());
	auto* newObj = iter->second.first->Clone();
	m_ObjectCloneMap[Name] = newObj;
	m_AddPending.emplace_back(std::pair{ iter->second.second, Type }, newObj);
	newObj->OnInitialize();
	newObj->GetTransform().SetPosition(Pos);
	return newObj;
}

void ObjectManager::Remove(const IObject* Info)
{
	m_DeletePending.emplace_back(Info->GetInfo());
}

IObject* ObjectManager::Get(const std::string& Name)
{
	auto iter = m_ObjectCloneMap.find(Name);
	assert(iter != m_ObjectCloneMap.end());
	return iter->second;
}

void ObjectManager::FixedUpdate(float dt)
{
	for(auto& var : m_Objects)
	{
		for(auto& dst : var)
		{
			dst->FixedUpdate(dt);
		}
	}
}

void ObjectManager::Update(float dt)
{
	for(auto& var : m_Objects)
	{
		for(auto& dst : var)
		{
			dst->OnUpdate(dt);
		}
	}
}

void ObjectManager::LateUpdate(float dt)
{
	for(auto& var : m_Objects)
	{
		for(auto& dst : var)
		{
			dst->LateUpdate(dt);
		}
	}
}

void ObjectManager::Render()
{
	for(auto& var : m_Objects)
	{
		for(auto& dst : var)
		{
			dst->OnRender();
		}
	}
}

void ObjectManager::Clear()
{
	SAFE_DELETE_VEC(m_Objects[static_cast<size_t>(CREATE_TYPE::DYNAMIC)]);

	for(auto& var : m_Render)
	{
		var.clear();
	}

	for(auto& [name, Ptr] : m_ObjectMap)
	{
		SAFE_DELETE(Ptr.first);
	}
}

void ObjectManager::Flush()
{
	FlushAdd();
	FlushRemove();
}

void ObjectManager::FlushAdd()
{
	if(m_AddPending.empty()) return;

	for(auto& [type, Obj] : m_AddPending)
	{
		if(type.second == RENDER_TYPE::NONE)
		{
			Obj->SetInfo(m_Objects[static_cast<size_t>(type.first)].size(), type.first, type.second, INVALID);
		}
		else
		{
			auto& renderer = m_Render[static_cast<size_t>(type.second)];
			Obj->SetInfo(m_Objects[static_cast<size_t>(type.first)].size(), type.first, type.second, renderer.size());

			renderer.emplace_back(Obj);
		}
		m_Objects[static_cast<size_t>(type.first)].emplace_back(Obj);
	}
	m_AddPending.clear();
}

void ObjectManager::FlushRemove()
{
	if(m_DeletePending.empty()) return;

	for(auto& var : m_DeletePending)
	{
		auto& Object = m_Objects[static_cast<size_t>(var.createType)];
		auto& obj = Object[var.objectID];
		size_t lastIndex = Object.size() - 1;

		if(var.objectID != lastIndex)
		{
			auto& lastObj = Object[lastIndex];
			Object[var.objectID] = lastObj;
			lastObj->SetID(var.objectID);
		}
		Object.pop_back();
		SAFE_DELETE(obj);

		if(var.renderType == RENDER_TYPE::NONE) continue;

		auto& renderer = m_Render[static_cast<size_t>(var.renderType)];
		size_t lastIdx = renderer.size() - 1;
		if(var.renderID != lastIdx)
		{
			auto& lastRender = renderer[lastIdx];
			renderer[var.renderID] = lastRender;
			lastRender->SetRenderID(var.renderID);
		}
		renderer.pop_back();
	}
	m_DeletePending.clear();
}
