#include "ComponentManager.h"

ComponentManager::ComponentManager(ObjectManager& Object)
	: m_Object(Object)
{}

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

void ComponentManager::Flush()
{
	for(auto& var : m_Object.GetDeleteObjects())
	{
		auto& delTransform = m_Transforms[var.objectID];
		size_t lastIndex = m_Transforms.size() - 1;
		SAFE_DELETE(delTransform);
		if(var.objectID != lastIndex)
		{
			auto& lastTransform = m_Transforms[lastIndex];
			m_Transforms[var.objectID] = lastTransform;
		}
		m_Transforms.pop_back();
	}
}

void ComponentManager::Clear()
{
	SAFE_DELETE_VEC(m_Transforms);
}