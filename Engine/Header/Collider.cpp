#include "Collider.h"

Collider::Collider(IObject* Owner, const ColliderInfo& Info)
	: m_Owner(Owner)
	, m_Info(Info)
{}

Collider::~Collider()
{
	SAFE_DELETE(m_AABB);
	m_Owner = nullptr;
}

void Collider::CreateAABB(const Vector3& Offset, const Vector3& HalfSize)
{
	m_AABB = new AABB(m_Owner->GetTransform(), Offset, HalfSize);
}

void Collider::CreateOBB(const Vector3& Offset)
{
	m_OBB = new OBB(m_Owner->GetTransform(), Offset);
}

IObject* Collider::GetOwner() const
{
	return m_Owner;
}

AABB* Collider::GetAABB()
{
	return m_AABB;
}

OBB* Collider::GetOBB()
{
	return m_OBB;
}

void Collider::Update()
{
	m_AABB->Update();
}

void Collider::Render(LPDEVICE Device)
{
	m_AABB->Render(Device);
}

const ColliderInfo& Collider::GetInfo() const
{
	return m_Info;
}

void Collider::SetID(size_t ID)
{
	m_Info.id = ID;
}