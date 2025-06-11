#include "ResourceManager.h"

ResourceManager::~ResourceManager()
{
	for(auto& [Name, Resource] : m_ResourceMap)
	{
		SAFE_DELETE(Resource);
	}
	m_ResourceMap.clear();
}

void ResourceManager::RegisterResource(const std::string& Name, IResource* Resource)
{
	auto iter = m_ResourceMap.find(Name);
	assert(iter == m_ResourceMap.end());
	m_ResourceMap.emplace(Name, Resource);
}

IResource* ResourceManager::GetResoucre(const std::string& Name)
{
	auto iter = m_ResourceMap.find(Name);
	assert(iter != m_ResourceMap.end());
	return iter->second;
}
