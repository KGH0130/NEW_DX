#pragma once
#include "CollderInfo.h"
#include "Engine_Macro.h"

BEGIN(Engine)
class DLL Collider
{
public:
	Collider(IObject* Owner, uint32_t Category, uint32_t Mask);
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
	bool IsTrigger() const;
	bool IsStatic() const;
	uint32_t GetCategory() const;
	uint32_t GetMask() const;

public:
	void SetInfo(ColliderInfo&& Info);
	void SetID(size_t ID);
	void SetTrigger(bool Trigger);
	void SetStatic(bool Static);

private:
	IObject* m_Owner = nullptr;
	AABB* m_AABB = nullptr;
	OBB* m_OBB = nullptr;

	bool m_IsTrigger = false;
	bool m_IsStatic = false;

	uint32_t m_Category = 0u;
	uint32_t m_Mask = 0u;

	ColliderInfo m_Info;
};
END