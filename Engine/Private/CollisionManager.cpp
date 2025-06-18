#include "CollisionManager.h"

CollisionManager::~CollisionManager()
{
	Clear();
}

Collider* CollisionManager::Init(IObject* Owner, REGION_TYPE type)
{
	auto& colliders = m_StaticColliders[static_cast<size_t>(type)];
	Collider* newColl = new Collider(Owner, ColliderInfo(colliders.size(), type));
	return m_StaticAddPending.emplace_back(type, newColl).second;
}

Collider* CollisionManager::Init(IObject* Owner, OBJECT_TYPE type)
{
	auto& colliders = m_DynamicColliders[static_cast<size_t>(type)];
	Collider* newColl = new Collider(Owner, ColliderInfo(colliders.size(), type));
	return m_DynamicAddPending.emplace_back(type, newColl).second;
}

void CollisionManager::Remove(const Collider* Collider)
{
	m_RemovePending.emplace_back(Collider->GetInfo());
}

void CollisionManager::Update()
{
	for(auto& var : m_DynamicColliders)
	{
		for(auto& dst : var)
		{
			dst->Update();
		}
	}
}

void CollisionManager::Render(LPDEVICE Device)
{
	for(auto& var : m_StaticColliders)
	{
		for(auto& dst : var)
		{
			dst->Render(Device);
		}
	}

	for(auto& var : m_DynamicColliders)
	{
		for(auto& dst : var)
		{
			dst->Render(Device);
		}
	}
}

void CollisionManager::Flush()
{
	FlushAdd();
	FlushRemove();
}

void CollisionManager::Clear()
{
	for(auto& var : m_StaticColliders)
	{
		SAFE_DELETE_VEC(var);
	}

	for(auto& var : m_DynamicColliders)
	{
		SAFE_DELETE_VEC(var);
	}
}

void CollisionManager::ProcessCollisions()
{
	CollisionSD(REGION_TYPE::NONE);

	CollisionDD(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ENEMY);


	CollisionEqual(OBJECT_TYPE::PLAYER);
}

void CollisionManager::FlushAdd()
{
	if(!m_StaticAddPending.empty())
	{
		for(auto& [type, collider] : m_StaticAddPending)
		{
			m_StaticColliders[static_cast<size_t>(type)].emplace_back(collider);
		}
		m_StaticAddPending.clear();
	}

	if(!m_DynamicAddPending.empty())
	{
		for(auto& [type, collider] : m_DynamicAddPending)
		{
			m_DynamicColliders[static_cast<size_t>(type)].emplace_back(collider);
		}
		m_DynamicAddPending.clear();
	}
}

void CollisionManager::FlushRemove()
{
	if(m_RemovePending.empty()) return;

	for(auto& var : m_RemovePending)
	{
		if(var.collType == COLLISION_TYPE::STATIC)
		{
			auto& colliders = m_StaticColliders[static_cast<size_t>(var.regiontype)];
			auto& delCollider = colliders[var.id];

			size_t last = colliders.size() - 1;
			if(var.id != last)
			{
				auto& lastCollider = colliders[last];
				delCollider = lastCollider;
				delCollider->SetID(var.id);
			}
			colliders.pop_back();

			SAFE_DELETE(delCollider);
		}
		else
		{
			auto& colliders = m_DynamicColliders[static_cast<size_t>(var.objType)];
			auto& delCollider = colliders[var.id];

			size_t last = colliders.size() - 1;
			if(var.id != last)
			{
				auto& lastCollider = colliders[last];
				delCollider = lastCollider;
				delCollider->SetID(var.id);
			}
			colliders.pop_back();

			SAFE_DELETE(delCollider);
		}
	}
	m_RemovePending.clear();
}

void CollisionManager::CollisionSD(REGION_TYPE Type)
{
	auto& STATIC = m_StaticColliders[static_cast<size_t>(Type)];

	for(auto& var : STATIC)
	{
		for(auto& dst : m_DynamicColliders)
		{
			for(auto& src : dst)
			{
				if(var->GetAABB()->IsInteraction(src->GetAABB()))
				{
					if(var->GetOBB()->IsInteraction(src->GetOBB()))
					{
						const auto& aOwner = var->GetOwner();
						const auto& bOwner = src->GetOwner();

						if(m_FrameExitSD.find(std::minmax(aOwner, bOwner)) == m_FrameExitSD.end())
						{
							aOwner->OnCollisionEnter(bOwner);
							bOwner->OnCollisionEnter(aOwner);
						}
						m_FrameEnterSD.emplace(std::minmax(aOwner, bOwner));
					}
				}
			}
		}
	}

	for(auto& var : m_FrameExitSD)
	{
		if(m_FrameEnterSD.find(var) == m_FrameEnterSD.end())
		{
			auto& dst = var.first;
			auto& src = var.second;

			dst->OnCollisionExit(src);
			src->OnCollisionExit(dst);
		}
	}

	m_FrameExitSD = std::move(m_FrameEnterSD);
}

void CollisionManager::CollisionDD(OBJECT_TYPE Dst, OBJECT_TYPE Src)
{
	auto& enterMap = m_FrameEnterDD[Dst][static_cast<size_t>(Src)];
	auto& exitMap = m_FrameExitDD[Dst][static_cast<size_t>(Src)];

	for(auto& var : m_DynamicColliders[static_cast<size_t>(Dst)])
	{
		for(auto& dst : m_DynamicColliders[static_cast<size_t>(Src)])
		{
			if(var->GetAABB()->IsInteraction(dst->GetAABB()))
			{
				if(var->GetOBB()->IsInteraction(dst->GetOBB()))
				{
					const auto& aOwner = var->GetOwner();
					const auto& bOwner = dst->GetOwner();

					if(exitMap.find(std::minmax(aOwner, bOwner)) == exitMap.end())
					{
						aOwner->OnCollisionEnter(bOwner);
						bOwner->OnCollisionEnter(aOwner);
					}
					enterMap.emplace(std::minmax(aOwner, bOwner));
				}
			}
		}
	}

	for(auto& var : exitMap)
	{
		if(enterMap.find(var) == enterMap.end())
		{
			const auto& aOwner = var.first;
			const auto& bOwner = var.second;

			aOwner->OnCollisionExit(bOwner);
			bOwner->OnCollisionExit(aOwner);
		}
	}

	exitMap = std::move(enterMap);
}

void CollisionManager::CollisionEqual(OBJECT_TYPE Type)
{
	auto& enterMap = m_FrameEqualEnter[Type];
	auto& exitMap = m_FrameEqualExit[Type];
	auto& collisions = m_DynamicColliders[static_cast<size_t>(Type)];
	size_t size = collisions.size();
	if(size < 2) return;

	for(int i = 0; i < size; ++i)
	{
		for(int j = i + 1; j < size; ++j)
		{
			if(collisions[i]->GetAABB()->IsInteraction(collisions[j]->GetAABB()))
			{
				if(collisions[i]->GetOBB()->IsInteraction(collisions[j]->GetOBB()))
				{
					const auto& aOwner = collisions[i]->GetOwner();
					const auto& bOwner = collisions[j]->GetOwner();

					if(exitMap.find(std::minmax(aOwner, bOwner)) == exitMap.end())
					{
						aOwner->OnCollisionEnter(bOwner);
						bOwner->OnCollisionEnter(aOwner);
					}
					enterMap.emplace(std::minmax(aOwner, bOwner));
				}
			}
		}
	}

	for(auto& var : exitMap)
	{
		if(enterMap.find(var) == enterMap.end())
		{
			const auto& dst = var.first;
			const auto& src = var.second;

			dst->OnCollisionExit(src);
			src->OnCollisionExit(dst);
		}
	}

	exitMap = std::move(enterMap);
}
