#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(GameInstance* Instance);

private:
	void Initialize() override;
	void InitState() override;
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
	void Move();
};

