#pragma once

class MainCamera : public IObject
{
public:
	MainCamera(GameInstance* Instance);

private:
	void Initialize() override;
	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void RenderEnter() override;
	void Render() override;
	void RenderExit() override;

private:
	void OnCollisionEnter(IObject* Other) override;
	void OnCollisionExit(IObject* Other) override;

private:
	IObject* Clone() override;

private:
	void UpdateViewMatrix();

private:
	IObject* m_Target = nullptr;

	Matrix m_MatProj;
	Matrix m_InverseMat;
	Vector3 m_Offset = VEC_ZERO;

	float m_Fov;
	float m_Aspect;
	float m_Near;
	float m_Far;
};