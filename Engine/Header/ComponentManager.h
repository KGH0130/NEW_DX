#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class IComponent;

class DLL ComponentManager
{
public:
	virtual ~ComponentManager();

public:
	void Clear();

public:
	template<typename T>
	void RegisterComponent(T* Ptr);

	template<typename T>
	T* GetComponent(T&& Value);

private:
	std::unordered_map<std::type_index, IComponent*> m_ComponentMap;
	std::vector<IComponent*> m_Components;
};

template<typename T>
inline void ComponentManager::RegisterComponent(T* Ptr)
{
	std::type_index index = std::type_index(typeid(T));
	auto iter = m_ComponentMap.find(index);
	assert(iter == m_ComponentMap.end());
	m_ComponentMap.emplace(index, Ptr);
}

template<typename T>
inline T* ComponentManager::GetComponent(T&& Value)
{
	auto iter = m_ComponentMap.find(std::type_index(typeid(T)));
	assert(iter != m_ComponentMap.end());
	auto comp = iter->second->Clone();
	m_Components.emplace_back(comp);
	T* newComp = static_cast<T*>(comp);
	*newComp = std::forward<T>(Value);
	return newComp;
}
END
