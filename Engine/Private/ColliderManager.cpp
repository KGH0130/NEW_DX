#include "ColliderManager.h"

void ColliderManager::Update()
{
	for(auto& var : m_AABB)
	{
		for(auto& dst : var)
		{
			dst.Update();
		}
	}
}

void ColliderManager::AddAABB(OBJECT_TYPE Type, const AABB& Aabb)
{
	m_AABB[static_cast<size_t>(Type)].emplace_back(Aabb);
}

bool ColliderManager::IsAABBCollision(OBJECT_TYPE Dst, OBJECT_TYPE Src)
{
	assert(Dst != Src);
	for(auto& a : m_AABB[static_cast<size_t>(Dst)])
	{
		for(auto& b : m_AABB[static_cast<size_t>(Src)])
		{
			//return (a.Min.x <= b.Max.x && a.Max.x >= b.Min.x)
			//	&& (a.Min.y <= b.Max.y && a.Max.y >= b.Min.y) 
			//	&&(a.Min.z <= b.Max.z && a.Max.z >= b.Min.z);
		}
	}
}
