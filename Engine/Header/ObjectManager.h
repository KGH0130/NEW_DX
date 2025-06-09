#pragma once
#include "Engine_Enum.h"
#include "Engine_Macro.h"
#include "ObjectInfo.h"

BEGIN(Engine)
class IObject;
class Transform;

class DLL ObjectManager
{
public:
	~ObjectManager();

public:
	void RegisterObject(const std::string& Name, IObject* Object);
	IObject* AddObject(RENDER_TYPE Type, const std::string& Name);
	void RemoveObject(const ObjectInfo& Info);

public:
	void FixedUpdate(float dt);
	void Update(float dt);
	void LateUpdate(float dt);
	void Render();

	void Clear();
	void Flush(std::vector<Transform*>& Transforms);
private:
	void FlushAdd();
	void FlushRemove();

private:
	std::unordered_map<std::string, IObject*> m_ObjectMap;

	std::vector<IObject*> m_Objects;
	std::vector<IObject*> m_Render[static_cast<size_t>(RENDER_TYPE::IDX)];

	std::vector<std::pair<RENDER_TYPE, IObject*>> m_AddPending;
	std::vector<ObjectInfo> m_DeletePending;
};
END