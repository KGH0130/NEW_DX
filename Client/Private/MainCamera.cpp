#include "MainCamera.h"

MainCamera::MainCamera(GameInstance* Instance)
	:IObject(Instance)
{
	m_Fov = D3DXToRadian(60.0f);
	m_Aspect = static_cast<float>(WINCX) / static_cast<float>(WINCY);
	m_Near = 0.1f;
	m_Far  = 1000.0f;
}

void MainCamera::Initialize()
{
	m_Target = instance->Object.Get_Object("Player");

}

void MainCamera::FixedUpdate(float dt)
{}

void MainCamera::Update(float dt)
{}

void MainCamera::LateUpdate(float dt)
{

	UpdateViewMatrix();
}

void MainCamera::RenderEnter()
{

}

void MainCamera::Render()
{}

void MainCamera::RenderExit()
{}

void MainCamera::OnCollisionEnter(IObject* Other)
{}

void MainCamera::OnCollisionExit(IObject* Other)
{}

IObject* MainCamera::Clone()
{
	return new MainCamera(instance);
}

void MainCamera::UpdateViewMatrix()
{
	m_InverseMat = m_Transform.GetWorldMatrix();
	D3DXMatrixInverse(&m_InverseMat, nullptr, &m_InverseMat);
	D3DXMatrixPerspectiveFovLH(&m_MatProj, m_Fov, m_Aspect, m_Near, m_Far);
	instance->Device->SetTransform(D3DTS_VIEW, &m_InverseMat);
	instance->Device->SetTransform(D3DTS_PROJECTION, &m_MatProj);
}
