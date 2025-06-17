#pragma once

class Entity : public IObject
{
public:
	Entity(GameInstance* Instance);
	virtual ~Entity() = default;

private:
	void OnInitialize() override;
	void OnUpdate(float dt) override;

private:
	void Initialize() override PURE;
	virtual void InitState() PURE;
	void FixedUpdate(float dt) override PURE;
	void Update(float dt) override PURE;
	void LateUpdate(float dt) override PURE;

	void RenderEnter() override PURE;
	void Render() override PURE;
	void RenderExit() override PURE;

private:
	void OnCollisionEnter(IObject* Other) override PURE;
	void OnCollisionExit(IObject* Other) override PURE;

private:
	IObject* Clone() override PURE;
protected:
	StateMachine m_StateMachine;
	RigidBody m_Rigid;
	Velocity m_Velocity;
};

