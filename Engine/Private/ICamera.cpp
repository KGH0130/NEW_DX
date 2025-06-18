#include "ICamera.h"

ICamera::ICamera(GameInstance* Instance)
	: instance(Instance)
{}

void ICamera::OnLateUpdate(float dt)
{
	LateUpdate(dt);
	if(m_Target)
	{
		m_Transform.SetPosition(m_Target->GetTransform().GetPosition() + m_Offset);
		UpdateViewMatrix();
		UpdateProjMatrix();
	}
}

void ICamera::SetTarget(IObject* Target)
{
	m_Target = Target;
	m_TragetTransform = &Target->GetTransform();
}

void ICamera::SetFov(float Fov)
{
	m_Fov = Fov;
	m_Dirty = true;
}

void ICamera::SetID(size_t ID)
{
	m_Info.id = ID;
}
size_t ICamera::GetID() const
{
	return m_Info.id;
}

void ICamera::UpdateViewMatrix()
{
	m_Transform.SetPosition(m_Target->GetTransform().GetPosition() + m_Offset);
	m_Transform.UpdateMatrix();
	m_InverseMat = m_Transform.GetWorldMatrix();
	D3DXMatrixInverse(&m_InverseMat, nullptr, &m_InverseMat);
	instance->Device->SetTransform(D3DTS_VIEW, &m_InverseMat);
}
void ICamera::UpdateProjMatrix()
{
	if(!m_Dirty) return;

	m_Dirty = false;
	D3DXMatrixPerspectiveFovLH(&m_MatProj, m_Fov, m_Aspect, m_Near, m_Far);
	instance->Device->SetTransform(D3DTS_PROJECTION, &m_MatProj);
}