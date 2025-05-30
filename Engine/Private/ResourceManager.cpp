#include "ResourceManager.h"

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::RegisterResource(const std::string& Name, IResource* Ptr)
{
	auto iter = m_ResourceMap.find(Name);
	assert(iter == m_ResourceMap.end());
	m_ResourceMap.emplace(Name, Ptr);
}

IResource* ResourceManager::GetResource(const std::string& Name)
{
	auto iter = m_ResourceMap.find(Name);
	assert(iter != m_ResourceMap.end());
	return iter->second;
}

void ResourceManager::Clear()
{
	for(auto& [name, Ptr] : m_ResourceMap)
	{
		SAFE_DELETE(Ptr);
	}
	m_ResourceMap.clear();
}