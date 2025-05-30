#include "ComponentManager.h"

ComponentManager::~ComponentManager()
{
	for(auto& var : m_Components)
	{
		var->Free();
		SAFE_DELETE(var);
	}
	m_Components.clear();

	for(auto& [type, Ptr] : m_ComponentMap)
	{
		Ptr->Free();
		SAFE_DELETE(Ptr);
	}
	m_ComponentMap.clear();
}
