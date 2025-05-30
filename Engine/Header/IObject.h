#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class DLL IObject : public IClone
{
public:
	IObject(GameInstance* Instance);
	virtual ~IObject() = default;

public:
	void OnRender();

public:
	void Initialize() override			PURE;
	virtual void FixedUpdate(float dt)	PURE;
	virtual void Update(float dt)		PURE;
	virtual void LateUpdate(float dt)	PURE;
	IClone* Clone() override	PURE;
	void Free() override		PURE;

private:
	virtual void RenderState()	PURE;
	virtual void Render()		PURE;

protected:
	GameInstance* instance;
};
END