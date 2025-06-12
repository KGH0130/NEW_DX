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