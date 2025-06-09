#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class Transform;
struct ObjectInfo;

class DLL ComponentManager
{
public:
	virtual ~ComponentManager();

public:
	Transform* CreateTransform();

	void TransformUpdate();
	std::vector<Transform*>& GetTransform();
	void Clear();

public:
	template<typename T, typename... Args>
	T* GetComponent(Args&&... Value);

private:
	std::vector<Transform*> m_Transforms;
};

template<typename T, typename... Args>
inline T* ComponentManager::GetComponent(Args&&... Value)
{
	T* newComp = new T(std::forward<Args>(Value)...);
	return newComp;
}
END
