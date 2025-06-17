#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class DLL OBB
{
public:
	OBB() = default;
	OBB(const Transform& Transform, const Vector3& Offset);

public:
	bool IsInteraction(const OBB* other);

	void Update();
	void Render(LPDEVICE Device) const;

private:
	const Transform& m_Transform;

	Vector3 m_Offset;

	Vector3 m_Center;
	Vector3 m_Axis[3];
	Vector3 m_Half;

	bool m_IsCollided = false;
};
END