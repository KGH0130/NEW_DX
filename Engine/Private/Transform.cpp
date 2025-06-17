#include "Transform.h"

Transform::Transform()
{
	D3DXMatrixIdentity(&m_WorldMat);
}

void Transform::SetPosition(const Vector3& pos)
{
	m_Position = pos;
	m_Dirty = true;
}

void Transform::SetRotation(const Vector3& rot)
{
	m_Rotation = rot;
	m_Dirty = true;
}

void Transform::SetScale(const Vector3& scale)
{
	m_Scale = scale;
	m_Dirty = true;
}

const Vector3& Transform::GetPosition() const
{
	return m_Position;
}

const Vector3& Transform::GetRotation() const
{
	return m_Rotation;
}

const Vector3& Transform::GetScale() const
{
	return m_Scale;
}

const Vector3 Transform::GetState(STATE State) const
{
	return m_WorldMat.m[static_cast<size_t>(State)];
}

const Matrix& Transform::GetWorldMatrix()
{
	UpdateMatrix();
	return m_WorldMat;
}

void Transform::UpdateMatrix()
{
	if(!m_Dirty) return;
	m_Dirty = false;

	D3DXMATRIX matScale, matRot, matTrans;

	D3DXMatrixScaling(&matScale, m_Scale.x, m_Scale.y, m_Scale.z);

	D3DXMatrixRotationYawPitchRoll(&matRot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

	D3DXMatrixTranslation(&matTrans, m_Position.x, m_Position.y, m_Position.z);

	m_WorldMat = matScale * matRot * matTrans;
}

bool Transform::IsDirty() const
{
	return m_Dirty;
}
