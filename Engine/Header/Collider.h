#pragma once
#include "CollderInfo.h"
#include "Engine_Macro.h"

BEGIN(Engine)
class DLL Collider
{
public:
	Collider(IObject* Owner, const ColliderInfo& Info);
	~Collider();

public:
	void CreateAABB(const Vector3& Offset, const Vector3& CheckSize);
	void CreateOBB(const Vector3& Offset);

public:
	IObject* GetOwner() const;
	AABB* GetAABB();
	OBB* GetOBB();

public:
	void Update();
	void Render(LPDEVICE Device);

public:
	const ColliderInfo& GetInfo() const;
	void SetID(size_t ID);

private:
	IObject* m_Owner = nullptr;
	AABB* m_AABB = nullptr;
	OBB* m_OBB = nullptr;

	ColliderInfo m_Info;
};
END