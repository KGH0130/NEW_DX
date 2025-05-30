#pragma once
#include "Engine_Enum.h"
#include "Engine_Macro.h"

BEGIN(Engine)
class IObject;

class DLL ObjectManager
{
public:
	~ObjectManager();

public:
	void RegisterObject(const std::string& Name, IObject* Ptr);
	IObject* AddObject(RENDERTYPE Type, const std::string& Name);

public:
	void FixedUpdate(float dt);
	void Update(float dt);
	void LateUpdate(float dt);
	void Render();

	void Clear();
private:
	std::unordered_map<std::string, IObject*> m_ObjectMap;

	std::vector<IObject*> m_Objects;
	std::vector<IObject*> m_Render[static_cast<size_t>(RENDERTYPE::IDX)];
};
END