#pragma once

class Entity : public IObject
{
public:
	Entity(GameInstance* Instance);
	virtual ~Entity() = default;

private:
	void Initialize() override PURE;
	virtual void InitState() PURE;
	void FixedUpdate(float dt) override PURE;
	void Update(float dt) override PURE;
	void LateUpdate(float dt) override PURE;

private:
	void OnCollisionEnter(IObject* Other) override PURE;
	void OnCollisionExit(IObject* Other) override PURE;

	IObject* Clone() override PURE;

private:
	void OnInitialize() override;
	void OnUpdate(float dt) override;

	void RenderEnter() override PURE;
	void Render() override PURE;
	void RenderExit() override PURE;

protected:
	StateMachine m_StateMachine;
};

