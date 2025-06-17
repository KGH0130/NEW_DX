#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
struct DLL Velocity
{
	Velocity() = default;
	Velocity(const Vector2& Vec)
		: dz(Vec.x), dy(Vec.y)
	{}
	Velocity(float Dx, float Dy)
		: dz(Dx), dy(Dy)
	{}

	Vector2 operator =(const Vector2& Vel) noexcept
	{
		dz = Vel.x;
		dy = Vel.y;
		return Vector2(dz, dy);
	}

	Vector2 operator =(const Vector3& Vel) noexcept
	{
		dz = Vel.x;
		dy = Vel.y;
		return Vector2(dz, dy);
	}

	Vector2 operator *(const Vector3& Vel) noexcept
	{
		float x = dz * Vel.x;
		float y = dz * Vel.y;
		return Vector2(x, y);
	}

	Vector2 operator *(const Vector2& Vel) noexcept
	{
		float x = dz * Vel.x;
		float y = dz * Vel.y;
		return Vector2(x, y);
	}

	float dz = 0.f, dy = 0.f;
};
END