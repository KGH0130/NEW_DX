#pragma once
#include "CollderInfo.h"
#include "Engine_Macro.h"

BEGIN(Engine)
class AABB;
class OBB;

class DLL Collider
{
public:
	Collider(const IObject* Owner, const ColliderInfo& Info);
	~Collider();

public:
	void CreateAABB(const Vector3& Offset, const Vector3& HalfSize);
	const IObject* GetOwner() const;

public:
	void Update();

public:
	const ColliderInfo& GetInfo() const;
	void SetID(size_t ID);

private:
	const IObject* m_Owner = nullptr;
	AABB* m_AABB = nullptr;
	OBB* m_OBB = nullptr;

	ColliderInfo m_Info;
};
END