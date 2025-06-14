#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class Collider;

class DLL AABB
{
public:
	AABB() = default;
	AABB(Transform& Transform, const Vector3& Offset, const Vector3& HalfSize);

public:
	void Update();
	void Render(LPDEVICE Device);
private:
	const Transform& m_Transform;

	Vector3 m_Offset;
	Vector3 m_HalfSize;

	Vector3 m_Min, m_Max;
};
END