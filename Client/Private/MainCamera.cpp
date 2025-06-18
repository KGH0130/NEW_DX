#include "ICamera.h"
#include "MainCamera.h"

MainCamera::MainCamera(GameInstance* Instance)
	: ICamera(Instance)
{
	m_Fov = D3DXToRadian(75.f);
	m_Aspect = static_cast<float>(WINCX) / static_cast<float>(WINCY);
	m_Near = 0.1f;
	m_Far  = 1000.0f;
}

void MainCamera::Initialize()
{}

void MainCamera::LateUpdate(float dt)
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


ICamera* MainCamera::Clone()
{
	return new MainCamera(*this);
}