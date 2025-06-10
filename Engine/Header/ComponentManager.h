#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class Transform;
class ObjectManager;

class DLL ComponentManager
{
public:
	ComponentManager(ObjectManager& Object);
	virtual ~ComponentManager();

public:
	Transform* CreateTransform();

	void TransformUpdate();
	void Flush();
	void Clear();

public:
	template<typename T, typename... Args>
	T* GetComponent(Args&&... Value);

private:
	std::vector<Transform*> m_Transforms;

	ObjectManager& m_Object;
};

template<typename T, typename... Args>
inline T* ComponentManager::GetComponent(Args&&... Value)
{
	T* newComp = new T(std::forward<Args>(Value)...);
	return newComp;
}
END
