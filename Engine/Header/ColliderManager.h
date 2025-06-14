#pragma once
#include "CollderInfo.h"
#include "Engine_Enum.h"
#include "Engine_Macro.h"

BEGIN(Engine)
class IObject;

class DLL ColliderManager
{
public:
	ColliderManager(LPDEVICE Device);
	~ColliderManager();

public:
	Collider* AddCollider(IObject* Owner, COLLISION_TYPE CollType, OBJECT_TYPE ObjectType);
	void RemoveCollider(const Collider* Collider);

public:
	void Update();
	void Flush();
	void Clear();
private:
	void FlushAdd();
	void FlushRemove();

private:
	std::array<std::array<std::vector<Collider*>, static_cast<size_t>(OBJECT_TYPE::IDX)>, static_cast<size_t>(COLLISION_TYPE::IDX)> m_Colloders;

	std::vector<std::pair<Collider*, std::pair<COLLISION_TYPE, OBJECT_TYPE>>> m_AddPending;
	std::vector<ColliderInfo> m_RemovePending;

	LPDEVICE m_Device = nullptr;
};
END