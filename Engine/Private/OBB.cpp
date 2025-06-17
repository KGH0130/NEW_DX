#include "OBB.h"

OBB::OBB(const Transform& Transform, const Vector3& Offset)
	: m_Transform(Transform)
	, m_Offset(Offset)
	, m_Center(Transform.GetPosition() + Offset)
	, m_Half(Transform.GetScale() * 0.5f)
{}

bool OBB::IsInteraction(const OBB* other)
{
	m_IsCollided = false;

	constexpr static float EPSILON = 1e-6f;

	const Vector3& b_Center = other->m_Center;
	const Vector3* b_Axis = other->m_Axis;
	const Vector3& b_Half = other->m_Half;

	Vector3 distance = b_Center - m_Center;

	float rotate[3][3]{};
	float absRotate[3][3]{};

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			rotate[i][j] = Dot(m_Axis[i], b_Axis[j]);
			absRotate[i][j] = std::abs(rotate[i][j]) + EPSILON;
		}
	}

	float distA[3]
	{
		Dot(distance, m_Axis[0]),
		Dot(distance, m_Axis[1]),
		Dot(distance, m_Axis[2]),
	};

	float distB[3]
	{
		Dot(distance, b_Axis[0]),
		Dot(distance, b_Axis[1]),
		Dot(distance, b_Axis[2]),
	};

	for(int i = 0; i < 3; ++i)
	{
		float rB = b_Half[0] * absRotate[i][0] + b_Half[1] * absRotate[i][1] + b_Half[2] * absRotate[i][2];
		if(std::abs(distA[i]) > m_Half[i] + rB) return false;
	}

	for(int i = 0; i < 3; ++i)
	{
		float rA = m_Half[0] * absRotate[0][i] + m_Half[1] * absRotate[1][i] + m_Half[2] * absRotate[2][i];
		if(std::abs(distB[i]) > rA + b_Half[i]) return false;
	}

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			float ra = m_Half[(i + 1) % 3] * absRotate[(i + 2) % 3][j] + m_Half[(i + 2) % 3] * absRotate[(i + 1) % 3][j];
			float rb = b_Half[(j + 1) % 3] * absRotate[i][(j + 2) % 3] + b_Half[(j + 2) % 3] * absRotate[i][(j + 1) % 3];

			float dist = std::abs(distA[(i + 2) % 3] * rotate[(i + 1) % 3][j] - distA[(i + 1) % 3] * rotate[(i + 2) % 3][j]);

			if(dist > ra + rb)
				return false;
		}
	}

	m_IsCollided = true;
	return true;
}

void OBB::Update()
{
	if(!m_Transform.IsDirty()) return;

	m_Center = m_Transform.GetPosition() + m_Offset;
	Vector3 rotateX = m_Transform.GetState(STATE::RIGHT);
	Vector3 rotateY = m_Transform.GetState(STATE::UP);
	Vector3 rotateZ = m_Transform.GetState(STATE::LOOK);

	D3DXVec3Normalize(&m_Axis[0], &rotateX);
	D3DXVec3Normalize(&m_Axis[1], &rotateY);
	D3DXVec3Normalize(&m_Axis[2], &rotateZ);

	m_Half = m_Transform.GetScale() * 0.5f;
}

void OBB::Render(LPDEVICE Device) const
{
	Vector3 x = m_Axis[0] * m_Half.x;
	Vector3 y = m_Axis[1] * m_Half.y;
	Vector3 z = m_Axis[2] * m_Half.z;

	Vector3 corners[8]
	{
		m_Center - x - y - z,
		m_Center + x - y - z,
		m_Center + x + y - z,
		m_Center - x + y - z,
		m_Center - x - y + z,
		m_Center + x - y + z,
		m_Center + x + y + z,
		m_Center - x + y + z
	};

	COLLIDER_VTX lineVertices[8];

	for(int i = 0; i < 8; ++i)
	{
		lineVertices[i].pos = corners[i];
		lineVertices[i].color = m_IsCollided ? D3DCOLOR_ARGB(0xFF, 0xFF, 0, 0) : D3DCOLOR_ARGB(0xFF, 0, 0xFF, 0);
	}

	WORD indices[24]
	{
		0,1, 1,2, 2,3, 3,0,
		4,5, 5,6, 6,7, 7,4,
		0,4, 1,5, 2,6, 3,7
	};

	Device->SetFVF(D3DFVF_COLLIDER);
	Device->DrawIndexedPrimitiveUP(D3DPT_LINELIST, 0, 8, 12, indices, D3DFMT_INDEX16, lineVertices, sizeof(COLLIDER_VTX));
}
