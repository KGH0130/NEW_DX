#include "RigidBody.h"

RigidBody::RigidBody(Transform& Transform)
	: m_Transform(Transform)
{}


void RigidBody::Update(const float dt)
{
	if(!m_Active) return;

	Vector3 pos = m_Transform.GetPosition();
	if(m_Gravity)
		pos.y += Gravity * m_GravityScale * dt;

	pos.z += m_Velocity.dz * dt;
	m_Transform.SetPosition(pos);
}

void RigidBody::SetVelocity(const Velocity& Velocity)
{
	m_Velocity = Velocity;
}

void RigidBody::SetVelocity(float Dx, float Dy)
{
	m_Velocity = Velocity(Dx, Dy);
}

void RigidBody::SetVelocity(const Vector2& Vec)
{
	m_Velocity = Vec;
}

void RigidBody::SetVelocity(const Vector3& Vec)
{
	m_Velocity = Vec;
}

void RigidBody::SetVelocityZ(const Vector2& Vec)
{
	m_Velocity.dz = Vec.x;
}

void RigidBody::SetVelocityY(const float Dy)
{
	m_Velocity.dy = Dy;
}

void RigidBody::SetGravityScale(const float Scale)
{
	m_GravityScale = Scale;
}

void RigidBody::SetGravity(const bool Gravity)
{
	m_Gravity = Gravity;
}
