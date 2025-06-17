#include "AABB.h"

AABB::AABB(Transform& Transform, const Vector3& Offset, const Vector3& CheckSize)
	: m_Transform(Transform)
	, m_Offset(Offset)
	, m_CheckSize(CheckSize)
	, m_Min(m_Transform.GetPosition() + Offset - CheckSize)
	, m_Max(m_Transform.GetPosition() + Offset + CheckSize)
{}

bool AABB::IsInteraction(const AABB* other)
{
	m_IsCollided = false;
	if(m_Max.x < other->m_Min.x || m_Min.x > other->m_Max.x) return false;
	if(m_Max.y < other->m_Min.y || m_Min.y > other->m_Max.y) return false;
	if(m_Max.z < other->m_Min.z || m_Min.z > other->m_Max.z) return false;

	m_IsCollided = true;
	return true;
}

void AABB::Update()
{
	if(!m_Transform.IsDirty()) return;

	const Vector3 pos = m_Transform.GetPosition();
	m_Min = pos + m_Offset - m_CheckSize;
	m_Max = pos + m_Offset + m_CheckSize;
}

void AABB::Render(LPDEVICE Device) const
{
	Vector3 corners[8]
	{
		{m_Min.x, m_Min.y, m_Min.z},
		{m_Max.x, m_Min.y, m_Min.z},
		{m_Min.x, m_Max.y, m_Min.z},
		{m_Max.x, m_Max.y, m_Min.z},
		{m_Min.x, m_Min.y, m_Max.z},
		{m_Max.x, m_Min.y, m_Max.z},
		{m_Min.x, m_Max.y, m_Max.z},
		{m_Max.x, m_Max.y, m_Max.z}
	};

	WORD indices[24]
	{
		0,1, 1,3, 3,2, 2,0,
		4,5, 5,7, 7,6, 6,4,
		0,4, 1,5, 2,6, 3,7
	};

	COLLIDER_VTX lineVertices[8];

	for(int i = 0; i < 8; ++i)
	{
		lineVertices[i].pos = corners[i];
		lineVertices[i].color = m_IsCollided ? D3DCOLOR_ARGB(0xFF, 0xFF, 0, 0) : D3DCOLOR_ARGB(0xFF, 0, 0xFF, 0);
	}

	Device->SetFVF(D3DFVF_COLLIDER);
	Device->DrawIndexedPrimitiveUP(D3DPT_LINELIST, 0, 8, 12, indices, D3DFMT_INDEX16, lineVertices, sizeof(COLLIDER_VTX));
}