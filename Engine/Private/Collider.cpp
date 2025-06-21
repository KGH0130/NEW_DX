#include "Collider.h"

Collider::Collider(IObject* Owner, uint32_t Category, uint32_t Mask)
	: m_Owner(Owner)
	, m_Category(Category)
	, m_Mask(Mask)
{}

Collider::~Collider()
{
	m_Owner = nullptr;
	SAFE_DELETE(m_AABB);
	SAFE_DELETE(m_OBB);
}

void Collider::CreateAABB(const Vector3& Offset, const Vector3& CheckSize)
{
	m_AABB = new AABB(m_Owner->GetTransform(), Offset, CheckSize);
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
	if(m_AABB) m_AABB->Update();

	if(m_OBB) m_OBB->Update();
}

void Collider::Render(LPDEVICE Device)
{
	if(m_AABB) m_AABB->Render(Device);

	if(m_OBB) m_OBB->Render(Device);
}

const ColliderInfo& Collider::GetInfo() const
{
	return m_Info;
}

bool Collider::IsTrigger() const
{
	return m_IsTrigger;
}

bool Collider::IsStatic() const
{
	return m_IsStatic;
}

uint32_t Collider::GetCategory() const
{
	return m_Category;
}

uint32_t Collider::GetMask() const
{
	return m_Mask;
}

void Collider::SetInfo(ColliderInfo&& Info)
{
	m_Info = std::move(Info);
}

void Collider::SetID(size_t ID)
{
	m_Info.id = ID;
}

void Collider::SetTrigger(bool Trigger)
{
	m_IsTrigger = Trigger;
}

void Collider::SetStatic(bool Static)
{
	m_IsStatic = Static;
}
