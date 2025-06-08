#include "ResourceManager.h"

ResourceManager::~ResourceManager()
{
	for(auto& [name, Ptr] : m_ResourceMap)
	{
		SAFE_DELETE(Ptr);
	}
	m_ResourceMap.clear();
}