#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class IComponent;
class Transform;

class DLL ComponentManager
{
public:
	virtual ~ComponentManager();

public:
	Transform* CreateTransform();

	void TransformUpdate();

	void Clear();

public:
	template<typename T, typename... Args>
	T* GetComponent(Args&&... Value);

private:
	std::vector<IComponent*> m_Components;
	std::vector<Transform*> m_Transforms;
};

template<typename T, typename... Args>
inline T* ComponentManager::GetComponent(Args&&... Value)
{
	T* newComp = new T(std::forward<Args>(Value)...);
	m_Components.emplace(newComp);
	return newComp;
}
END
