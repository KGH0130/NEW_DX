#pragma once
#include "Engine_Enum.h"
#include "Engine_Hash.h"
#include "Engine_Macro.h"
#include "ObjectInfo.h"

BEGIN(Engine)
class IObject;

class DLL ObjectManager
{
public:
	~ObjectManager();

public:
	void Register(const std::string& Name, IObject* Object, CREATE_TYPE Type = CREATE_TYPE::DYNAMIC);
	IObject* Init(RENDER_TYPE Type, const std::string& Name, Vector3 Pos = VEC_ZERO);
	void Remove(const IObject* Obj);
	IObject* Get(const std::string& Name);

public:
	void FixedUpdate(float dt);
	void Update(float dt);
	void LateUpdate(float dt);
	void Render();

public:
	void Flush();
	void Clear();
private:
	void FlushAdd();
	void FlushRemove();

private:
	std::unordered_map<std::string, std::pair<IObject*, CREATE_TYPE>> m_ObjectMap;

	std::unordered_map<std::string, IObject*> m_ObjectCloneMap;
	std::array<std::vector<IObject*>, static_cast<size_t>(CREATE_TYPE::IDX)> m_Objects;
	std::array<std::vector<IObject*>, static_cast<size_t>(RENDER_TYPE::IDX)> m_Render;

	std::vector<std::pair<std::pair<CREATE_TYPE, RENDER_TYPE>, IObject*>> m_AddPending;
	std::vector<ObjectInfo> m_DeletePending;
};
END