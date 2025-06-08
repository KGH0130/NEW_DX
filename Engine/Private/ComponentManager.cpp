#include "ComponentManager.h"

ComponentManager::~ComponentManager()
{
	Clear();
}

Transform* ComponentManager::CreateTransform()
{
	Transform* newTransform = new Transform;
	m_Transforms.emplace_back(newTransform);
	return newTransform;
}

void ComponentManager::TransformUpdate()
{
	for(auto& var : m_Transforms)
	{
		var->UpdateMatrix();
	}
}

void ComponentManager::Clear()
{
	SAFE_DELETE_VEC(m_Components);
	SAFE_DELETE_VEC(m_Transforms);
}