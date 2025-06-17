#pragma once
#include "Engine_Macro.h"
#include "Velocity.h"

BEGIN(Engine)
class Transform;

class DLL RigidBody
{
public:
	RigidBody(Transform& Transform);

public:
	void Update(const float dt);

	void SetVelocity(const Velocity& Velocity);
	void SetVelocity(float Dx, float Dy);
	void SetVelocity(const Vector2& Vec);
	void SetVelocity(const Vector3& Vec);
	void SetVelocityZ(const Vector2& Vec);
	void SetVelocityY(const float Dy);

	void SetGravityScale(const float Scale);

	void SetGravity(const bool Gravity);

private:
	Transform& m_Transform;
	Velocity m_Velocity;

	bool m_Active = true;
	bool m_Gravity = true;

	float m_GravityScale = 1.f;
	static constexpr float Gravity = -9.81f;

};
END