#pragma once
#include "CameraInfo.h"
#include "Engine_Macro.h"
#include "IClone.h"
#include "Transform.h"

BEGIN(Engine)
class IObject;
struct GameInstance;

class DLL ICamera : public IClone
{
public:
	ICamera(GameInstance* Instance);
	virtual ~ICamera() = default;

public:
	void OnLateUpdate(float dt);

public:
	virtual void Initialize() PURE;
	virtual void LateUpdate(float dt) PURE;

public:
	void SetTarget(IObject* Target);
	void SetFov(float Fov);
	void SetID(size_t ID);
	size_t GetID() const;

public:
	ICamera* Clone() override PURE;

private:
	void UpdateViewMatrix();
	void UpdateProjMatrix();

protected:
	IObject* m_Target = nullptr;
	Transform* m_TragetTransform = nullptr;
	GameInstance* instance = nullptr;

	Transform m_Transform;
	Matrix m_InverseMat;
	Matrix m_MatProj;
	Vector3 m_Offset = VEC_ZERO;
	CameraInfo m_Info;

	bool m_Dirty = true;

	float m_Fov = 0.f;
	float m_Aspect = 0.f;
	float m_Near = 0.f;
	float m_Far = 0.f;
};
END