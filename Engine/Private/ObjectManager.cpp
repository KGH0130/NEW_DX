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
	auto iter = m_ObjectMap.find(Name);
	assert(iter != m_ObjectMap.end());
	auto* newObj = iter->second->Clone();
	m_AddPending.emplace_back(Type, newObj);
	newObj->Initialize();
	return newObj;
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

void ObjectManager::Flush(std::vector<Transform*>& Transforms)
{
	for(auto& var : m_DeletePending)
	{
		auto& delTransform = Transforms[var.objectID];
		size_t lastIndex = Transforms.size() - 1;
		SAFE_DELETE(delTransform);
		if(var.objectID != lastIndex)
		{
			auto& lastTransform = Transforms[lastIndex];
			Transforms[var.objectID] = lastTransform;
		}
		Transforms.pop_back();
	}

	FlushRemove();
	FlushAdd();
}

void ObjectManager::FlushAdd()
{
	for(auto& [type, Obj] : m_AddPending)
	{
		if(type == RENDER_TYPE::NONE)
		{
			Obj->SetInfo(m_Objects.size(), type, INVALID);
		}
		else
		{
			Obj->SetInfo(m_Objects.size(), type, m_Render->size());
			m_Render->emplace_back(Obj);
		}
		m_Objects.emplace_back(Obj);
	}
	m_AddPending.clear();
}

void ObjectManager::FlushRemove()
{
	for(auto& var : m_DeletePending)
	{
		auto& obj = m_Objects[var.objectID];
		size_t lastIndex = m_Objects.size() - 1;

		SAFE_DELETE(obj);

		if(var.objectID != lastIndex)
		{
			auto& lastObj = m_Objects[lastIndex];
			m_Objects[var.objectID] = lastObj;
			lastObj->SetID(var.objectID);
		}
		m_Objects.pop_back();

		if(var.type == RENDER_TYPE::NONE) continue;

		auto& renderer = m_Render[static_cast<size_t>(var.type)];
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
