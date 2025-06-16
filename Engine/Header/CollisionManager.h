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
	Collider* AddCollider(IObject* Owner, COLLISION_TYPE CollType, OBJECT_TYPE ObjectType);
	void RemoveCollider(const Collider* Collider);

public:
	void Update();
	void Render(LPDEVICE Device);
	void Flush();
	void Clear();

public:
	void IsCollisionCheck();

private:
	void FlushAdd();
	void FlushRemove();

private:
	std::array<std::array<std::vector<Collider*>, static_cast<size_t>(OBJECT_TYPE::IDX)>, static_cast<size_t>(COLLISION_TYPE::IDX)> m_Colloders;

	std::vector<std::pair<Collider*, std::pair<COLLISION_TYPE, OBJECT_TYPE>>> m_AddPending;
	std::vector<ColliderInfo> m_RemovePending;

	std::unordered_set<std::pair<IObject*, IObject*>, CollisionHash> m_FrameEnter;
	std::unordered_set<std::pair<IObject*, IObject*>, CollisionHash> m_FrameExit;
};
END