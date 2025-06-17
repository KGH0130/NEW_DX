#include "MainCamera.h"

MainCamera::MainCamera(GameInstance* Instance)
	:IObject(Instance)
{
	m_Fov = D3DXToRadian(75.f);
	m_Aspect = static_cast<float>(WINCX) / static_cast<float>(WINCY);
	m_Near = 0.1f;
	m_Far  = 1000.0f;
}

void MainCamera::Initialize()
{
	UpdateViewMatrix();

	m_Target = instance->Object.Get("Player");
}

void MainCamera::FixedUpdate(float dt)
{}

void MainCamera::Update(float dt)
{
	const bool UP = instance->Input.GetKey(W);
	const bool DOWN  = instance->Input.GetKey(S);
	const bool LEFT = instance->Input.GetKey(A);
	const bool RIGHT = instance->Input.GetKey(D);

	if(UP || DOWN)
	{
		Vector3 look = m_Transform.GetState(STATE::LOOK);
		D3DXVec3Normalize(&look, &look);
		look.y = 0.f;

		if(UP)
			m_Offset += look * dt;
		if(DOWN)
			m_Offset -= look * dt;
	}

	if(LEFT || RIGHT)
	{
		Vector3 right = m_Transform.GetState(STATE::RIGHT);
		D3DXVec3Normalize(&right, &right);
		right.y = 0.f;

		if(LEFT)
			m_Offset -= right * dt;
		if(RIGHT)
			m_Offset += right * dt;
	}
}

void MainCamera::LateUpdate(float dt)
{


	m_Transform.SetPosition(m_Target->GetTransform().GetPosition() + m_Offset);
	UpdateViewMatrix();
}

void MainCamera::RenderEnter()
{

}

void MainCamera::Render()
{}

void MainCamera::RenderExit()
{}

void MainCamera::SetFov(float Fov)
{
	m_Dirty = true;
	m_Fov = Fov;
}

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
	m_Transform.UpdateMatrix();

	m_InverseMat = m_Transform.GetWorldMatrix();
	D3DXMatrixInverse(&m_InverseMat, nullptr, &m_InverseMat);
	instance->Device->SetTransform(D3DTS_VIEW, &m_InverseMat);

	if(m_Dirty)
	{
		m_Dirty = false;
		D3DXMatrixPerspectiveFovLH(&m_MatProj, m_Fov, m_Aspect, m_Near, m_Far);
		instance->Device->SetTransform(D3DTS_PROJECTION, &m_MatProj);
	}
}
