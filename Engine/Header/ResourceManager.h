#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class IResource;

class DLL ResourceManager
{
public:
	~ResourceManager();

public:
	template<typename T, typename... Args>
	IResource* GetResource(Args&&... Value);

private:
	std::unordered_map<std::type_index, IResource*> m_ResourceMap;
};

template<typename T, typename ...Args>
inline IResource* ResourceManager::GetResource(Args&& ...Value)
{
	std::type_index index(typeid(T));
	auto iter = m_ResourceMap.find(index);
	if(iter != m_ResourceMap.end())
		return iter->second;

	T* newResource = new T(std::forward<Args>(Value)...);
	m_ResourceMap.emplace(index, newResource);
	return newResource;
}
END