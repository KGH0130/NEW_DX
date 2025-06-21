#pragma once
#include "CollderInfo.h"
#include "CollisionHash.h"
#include "Engine_Enum.h"
#include "Engine_Macro.h"

BEGIN(Engine)
class IObject;

class DLL CollisionManager
{
public:
	~CollisionManager();

public:
	Collider* Init(IObject* Owner, REGION_TYPE type, uint32_t Category, uint32_t Mask);
	Collider* Init(IObject* Owner, OBJECT_TYPE type, uint32_t Category, uint32_t Mask);

	void Release(const Collider* Collider);

public:
	void Update();
	void Render(LPDEVICE Device);
	void Flush();
	void Clear();

public:
	void ProcessCollisions();

private:
	void FlushAdd();
	void FlushRemove();

private:
	void CollisionSD(REGION_TYPE Type);
	void CollisionDD(OBJECT_TYPE Dst);
	void CollisionEqual(OBJECT_TYPE Type);

	bool ShouldCollide(const Collider* Dst, const Collider* Src);

private:
	std::array<std::vector<Collider*>, static_cast<size_t>(REGION_TYPE::IDX)> m_StaticColliders;
	std::vector<std::pair<REGION_TYPE, Collider*>> m_StaticAddPending;

	std::array<std::vector<Collider*>, static_cast<size_t>(OBJECT_TYPE::IDX)> m_DynamicColliders;
	std::vector<std::pair<OBJECT_TYPE, Collider*>> m_DynamicAddPending;

	std::vector<ColliderInfo> m_RemovePending;

	std::unordered_set<std::pair<IObject*, IObject*>, CollisionHash> m_FrameEnterSD;
	std::unordered_set<std::pair<IObject*, IObject*>, CollisionHash> m_FrameExitSD;

	std::unordered_map<OBJECT_TYPE, std::array<std::unordered_set<std::pair<IObject*, IObject*>, CollisionHash>, static_cast<size_t>(OBJECT_TYPE::IDX)>> m_FrameEnterDD;
	std::unordered_map<OBJECT_TYPE, std::array<std::unordered_set<std::pair<IObject*, IObject*>, CollisionHash>, static_cast<size_t>(OBJECT_TYPE::IDX)>> m_FrameExitDD;

	std::unordered_map<OBJECT_TYPE, std::unordered_set<std::pair<IObject*, IObject*>, CollisionHash>> m_FrameEqualEnter;
	std::unordered_map<OBJECT_TYPE, std::unordered_set<std::pair<IObject*, IObject*>, CollisionHash>> m_FrameEqualExit;
};
END