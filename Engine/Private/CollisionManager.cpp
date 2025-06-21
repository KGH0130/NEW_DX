#include "CollisionManager.h"

CollisionManager::~CollisionManager()
{
	Clear();
}

Collider* CollisionManager::Init(IObject* Owner, REGION_TYPE type, uint32_t Category, uint32_t Mask)
{
	return m_StaticAddPending.emplace_back(type, new Collider(Owner, Category, Mask)).second;
}

Collider* CollisionManager::Init(IObject* Owner, OBJECT_TYPE type, uint32_t Category, uint32_t Mask)
{
	return m_DynamicAddPending.emplace_back(type, new Collider(Owner, Category, Mask)).second;
}

void CollisionManager::Release(const Collider* Collider)
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

	CollisionDD(OBJECT_TYPE::PLAYER);

	CollisionEqual(OBJECT_TYPE::PLAYER);
}

void CollisionManager::FlushAdd()
{
	if(!m_StaticAddPending.empty())
	{
		for(auto& [type, collider] : m_StaticAddPending)
		{
			auto& colliders = m_StaticColliders[static_cast<size_t>(type)];
			collider->SetInfo(ColliderInfo(colliders.size(), type));
			colliders.emplace_back(collider);
		}
		m_StaticAddPending.clear();
	}

	if(!m_DynamicAddPending.empty())
	{
		for(auto& [type, collider] : m_DynamicAddPending)
		{
			auto& colliders = m_DynamicColliders[static_cast<size_t>(type)];
			collider->SetInfo(ColliderInfo(m_DynamicColliders.size(), type));
			colliders.emplace_back(collider);
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
				colliders[var.id] = lastCollider;
				lastCollider->SetID(var.id);
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
				colliders[var.id] = lastCollider;
				lastCollider->SetID(var.id);
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
				if(!ShouldCollide(var, src)) continue;

				if(var->GetAABB()->IsInteraction(src->GetAABB()))
				{
					Vector3 mtv;
					if(var->GetOBB()->IsInteraction(src->GetOBB(), &mtv))
					{
						const auto& aOwner = var->GetOwner();
						const auto& bOwner = src->GetOwner();

						if(!src->IsTrigger())
							bOwner->GetTransform().Translate(-mtv);

						if(!m_FrameExitSD.count(std::minmax(aOwner, bOwner)))
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

void CollisionManager::CollisionDD(OBJECT_TYPE Dst)
{
	size_t index = 0ull;

	auto& enterMap = m_FrameEnterDD[Dst][index];
	auto& exitMap = m_FrameExitDD[Dst][index];

	for(auto& var : m_DynamicColliders[static_cast<size_t>(Dst)])
	{
		for(auto& dst : m_DynamicColliders)
		{
			for(auto& src : dst)
			{
				if(!ShouldCollide(var, src) || var->GetCategory() == src->GetCategory())
					continue;

				if(var->GetAABB()->IsInteraction(src->GetAABB()))
				{
					Vector3 mtv;
					if(var->GetOBB()->IsInteraction(src->GetOBB(), &mtv))
					{
						const auto& aOwner = var->GetOwner();
						const auto& bOwner = src->GetOwner();

						if(!var->IsTrigger() && !src->IsTrigger())
						{
							auto& aTransform = aOwner->GetTransform();
							auto& bTransform = bOwner->GetTransform();

							if(var->IsStatic())
								bTransform.Translate(mtv);
							else if(src->IsStatic())
								aTransform.Translate(mtv);
							else
							{
								aTransform.Translate(-mtv * 0.5f);
								bTransform.Translate(mtv * 0.5f);
							}
						}

						if(!exitMap.count(std::minmax(aOwner, bOwner)))
						{
							aOwner->OnCollisionEnter(bOwner);
							bOwner->OnCollisionEnter(aOwner);
						}
						enterMap.emplace(std::minmax(aOwner, bOwner));
					}
				}
				for(auto& exitPair : exitMap)
				{
					if(enterMap.count(exitPair))
					{
						const auto& aOwner = exitPair.first;
						const auto& bOwner = exitPair.second;

						aOwner->OnCollisionExit(bOwner);
						bOwner->OnCollisionExit(aOwner);
					}
				}
				exitMap = std::move(enterMap);
			}
			++index;
		}
	}
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
				Vector3 mtv;
				if(collisions[i]->GetOBB()->IsInteraction(collisions[j]->GetOBB(), &mtv))
				{
					const auto& aOwner = collisions[i]->GetOwner();
					const auto& bOwner = collisions[j]->GetOwner();

					if(!collisions[i]->IsTrigger() && !collisions[j]->IsTrigger())
					{
						auto& aTransform = aOwner->GetTransform();
						auto& bTransform = bOwner->GetTransform();

						if(collisions[i]->IsStatic())
							bTransform.Translate(mtv);
						else if(collisions[j]->IsStatic())
							aTransform.Translate(mtv);
						else
						{
							aTransform.Translate(-mtv * 0.5f);
							bTransform.Translate(mtv * 0.5f);
						}
					}

					if(!exitMap.count(std::minmax(aOwner, bOwner)))
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

bool CollisionManager::ShouldCollide(const Collider* Dst, const Collider* Src)
{
	return (Dst->GetMask() & Src->GetCategory()) != 0
		&& (Src->GetMask() & Dst->GetCategory()) != 0;
}
