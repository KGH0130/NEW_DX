#include "AABB.h"

AABB::AABB(const Transform& Transform, const Vector3& Offset, const Vector3& HalfSize)
	: m_Transform(Transform)
	, m_Offset(Offset)
	, m_HalfSize(HalfSize)
	, m_Min(m_Transform.GetPosition() + Offset - HalfSize)
	, m_Max(m_Transform.GetPosition() + Offset + HalfSize)

{}

void AABB::Update()
{
	const Vector3 pos = m_Transform.GetPosition();
	m_Min = pos + m_Offset - m_HalfSize;
	m_Max = pos + m_Offset + m_HalfSize;
}
