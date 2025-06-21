#pragma once
#include "Engine_Macro.h"
#include "Engine_Typedef.h"

BEGIN(Engine)
class DLL Transform
{
public:
	Transform();

public:
	void SetPosition(const Vector3& pos);
	void SetRotation(const Vector3& rot);
	void SetScale(const Vector3& scale);

	void Translate(const Vector3& Pos);

	const Vector3& GetPosition() const;
	const Vector3& GetRotation() const;
	const Vector3& GetScale() const;

	const Vector3 GetState(STATE State) const;

	const Matrix& GetWorldMatrix();
	void UpdateMatrix();

	bool IsDirty() const;

private:
	Vector3 m_Position = VEC_ZERO;
	Vector3 m_Rotation = VEC_ZERO;
	Vector3 m_Scale = Vector3(1.f, 1.f, 1.f);

	Matrix m_WorldMat;

	bool m_Dirty = true;
};
END