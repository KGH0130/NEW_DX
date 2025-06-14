#include "ColliderManager.h"

ColliderManager::ColliderManager(LPDEVICE Device)
	: m_Device(Device)
{}

ColliderManager::~ColliderManager()
{
	Clear();
}

Collider* ColliderManager::AddCollider(IObject* Owner, COLLISION_TYPE CollType, OBJECT_TYPE ObjType)
{
	auto& collisions = m_Colloders[static_cast<size_t>(CollType)][static_cast<size_t>(ObjType)];
	Collider* newCollider = new Collider(Owner, ColliderInfo(collisions.size(), CollType, ObjType));
	m_AddPending.emplace_back(std::pair{ newCollider, std::pair{CollType, ObjType} });
	return newCollider;
}

void ColliderManager::RemoveCollider(const Collider* Collider)
{
	m_RemovePending.emplace_back(Collider->GetInfo());
}


void ColliderManager::Update()
{
	for(auto& var : m_Colloders)
	{
		if(var == m_Colloders[static_cast<size_t>(COLLISION_TYPE::STATIC)])
			continue;

		for(auto& Dst : var)
		{
			for(auto& Src : Dst)
			{
				Src->Update();
				#ifdef _DEBUG
				Src->Render(m_Device);
				#endif

			}
		}
	}
}

void ColliderManager::Flush()
{
	FlushRemove();
	FlushAdd();
}

void ColliderManager::Clear()
{
	for(auto& var : m_Colloders)
	{
		for(auto& Dst : var)
		{
			SAFE_DELETE_VEC(Dst);
		}
	}
}

void ColliderManager::FlushAdd()
{
	if(m_AddPending.empty()) return;

	for(auto& var : m_AddPending)
	{
		auto& collisions = m_Colloders[static_cast<size_t>(var.second.first)][static_cast<size_t>(var.second.second)];
		collisions.emplace_back(var.first);
	}
	m_AddPending.clear();
}

void ColliderManager::FlushRemove()
{
	if(m_RemovePending.empty()) return;

	for(auto& var : m_RemovePending)
	{
		auto& collisions = m_Colloders[static_cast<size_t>(var.collType)][static_cast<size_t>(var.objType)];
		auto& obj = collisions[var.id];
		size_t lastIndex = collisions.size() - 1;
		SAFE_DELETE(obj);
		if(var.id != lastIndex)
		{
			auto& lastCollider = collisions[lastIndex];
			collisions[var.id] = lastCollider;
			lastCollider->SetID(var.id);
		}
		collisions.pop_back();
	}
	m_RemovePending.clear();
}