#include "ObjectManager.h"

ObjectManager::~ObjectManager()
{
	Clear();
}

void ObjectManager::RegisterObject(const std::string& Name, IObject* Object, CREATE_TYPE Type)
{
	auto iter = m_ObjectMap.find(Name);
	if(iter != m_ObjectMap.end())
	{
		SAFE_DELETE(Object);
		assert(false);
	}
	m_ObjectMap.emplace(Name, std::pair{ Object, Type });
}

IObject* ObjectManager::AddObject(RENDER_TYPE Type, const std::string& Name, Vector3 Pos)
{
	auto iter = m_ObjectMap.find(Name);
	assert(iter != m_ObjectMap.end());
	auto* newObj = iter->second.first->Clone();
	m_ObejctCloneMap[Name] = newObj;
	m_AddPending.emplace_back(std::pair{ iter->second.second, Type }, newObj);
	newObj->OnInitialize();
	newObj->GetTransform().SetPosition(Pos);
	return newObj;
}

void ObjectManager::RemoveObject(const IObject* Info)
{
	m_DeletePending.emplace_back(Info->GetInfo());
}

IObject* ObjectManager::Get_Object(const std::string& Name)
{
	auto iter = m_ObejctCloneMap.find(Name);
	assert(iter != m_ObejctCloneMap.end());
	return iter->second;
}

void ObjectManager::FixedUpdate(float dt)
{}
void ObjectManager::Update(float dt)
{}
void ObjectManager::LateUpdate(float dt)
{}
void ObjectManager::Render()
{}

void ObjectManager::Clear()
{
	//SAFE_DELETE_VEC(m_Objects[CREATE_TYPE::DYNAMIC]);

	for(auto& var : m_Render)
	{
		var.clear();
	}

	for(auto& [name, Ptr] : m_ObjectMap)
	{
		SAFE_DELETE(Ptr);
	}
}

void ObjectManager::Flush()
{
	FlushRemove();
	FlushAdd();
}

void ObjectManager::FlushAdd()
{
	if(m_AddPending.empty()) return;

	for(auto& [type, Obj] : m_AddPending)
	{
		if(type.second == RENDER_TYPE::NONE)
		{
			if(type.first == CREATE_TYPE::DYNAMIC)
				Obj->SetInfo(m_Objects[static_cast<size_t>(type.first)].size(), type.first, type.second, INVALID);
			else if(type.first == CREATE_TYPE::STATIC)
				Obj->SetInfo(m_Objects[static_cast<size_t>(type.first)].size(), type.first, type.second, INVALID);
		}
		else
		{
			auto& renderer = m_Render[static_cast<size_t>(type.second)];
			if(type.first == CREATE_TYPE::DYNAMIC)
				Obj->SetInfo(m_Objects[static_cast<size_t>(type.first)].size(), type.first, type.second, renderer.size());
			else if(type.first == CREATE_TYPE::STATIC)
				Obj->SetInfo(m_Objects[static_cast<size_t>(type.first)].size(), type.first, type.second, renderer.size());

			renderer.emplace_back(Obj);
		}
		if(type.first == CREATE_TYPE::DYNAMIC)
			m_Objects[static_cast<size_t>(type.first)].emplace_back(Obj);
		else if(type.first == CREATE_TYPE::STATIC)
			m_Objects[static_cast<size_t>(type.first)].emplace_back(Obj);
	}
	m_AddPending.clear();
}

void ObjectManager::FlushRemove()
{
	if(m_DeletePending.empty()) return;

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
