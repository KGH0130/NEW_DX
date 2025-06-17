#include "CollisionManager.h"

CollisionManager::~CollisionManager()
{
	Clear();
}

Collider* CollisionManager::AddCollider(IObject* Owner, COLLISION_TYPE CollType, OBJECT_TYPE ObjType)
{
	auto& collisions = m_Colloders[static_cast<size_t>(CollType)][static_cast<size_t>(ObjType)];
	Collider* newCollider = new Collider(Owner, ColliderInfo(collisions.size(), CollType, ObjType));
	m_AddPending.emplace_back(std::pair{ newCollider, std::pair{CollType, ObjType} });
	return newCollider;
}

void CollisionManager::RemoveCollider(const Collider* Collider)
{
	m_RemovePending.emplace_back(Collider->GetInfo());
}


void CollisionManager::Update()
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
			}
		}
	}
}

void CollisionManager::Render(LPDEVICE Device)
{
	for(auto& var : m_Colloders)
	{
		for(auto& Dst : var)
		{
			for(auto& Src : Dst)
			{
				Src->Render(Device);
			}
		}
	}
}

void CollisionManager::Flush()
{
	FlushRemove();
	FlushAdd();
}

void CollisionManager::Clear()
{
	for(auto& var : m_Colloders)
	{
		for(auto& Dst : var)
		{
			SAFE_DELETE_VEC(Dst);
		}
	}
}

void CollisionManager::IsCollisionCheck()
{
	for(auto& var : m_Colloders)
	{
		for(auto& Dst : var)
		{
			size_t size = Dst.size();
			if(size < 2) continue;

			for(uint16_t i = 0; i < size; ++i)
			{
				for(uint16_t j = i + 1; j < size; ++j)
				{
					if(Dst[i]->GetAABB()->IsInteraction(Dst[j]->GetAABB()))
					{
						if(Dst[i]->GetOBB()->IsInteraction(Dst[j]->GetOBB()))
						{
							const auto& aOwner = Dst[i]->GetOwner();
							const auto& bOwner = Dst[j]->GetOwner();

							aOwner->OnCollisionEnter(bOwner);
							bOwner->OnCollisionEnter(aOwner);

							m_FrameEnter.emplace(std::minmax(aOwner, bOwner));
						}
					}
				}
			}
		}
	}

	for(auto& var : m_FrameExit)
	{
		if(m_FrameEnter.find(var) == m_FrameEnter.end())
		{
			const auto& dst = var.first;
			const auto& Src = var.second;
			dst->OnCollisionExit(Src);
			Src->OnCollisionExit(dst);
		}
	}

	m_FrameExit = std::move(m_FrameEnter);
}

void CollisionManager::FlushAdd()
{
	if(m_AddPending.empty()) return;

	for(auto& var : m_AddPending)
	{
		auto& collisions = m_Colloders[static_cast<size_t>(var.second.first)][static_cast<size_t>(var.second.second)];
		collisions.emplace_back(var.first);
	}
	m_AddPending.clear();
}

void CollisionManager::FlushRemove()
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