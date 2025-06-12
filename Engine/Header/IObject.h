#pragma once
#include "Engine_Macro.h"
#include "ObjectInfo.h"
#include "StateMachine.h"

BEGIN(Engine)
class Transform;
struct GameInstance;

class DLL IObject : public IClone
{
public:
	IObject(GameInstance* Instance);
	virtual ~IObject() = default;

public:
	void OnInitialize();
	void OnUpdate(float dt);
	void OnRender();

public:
	const ObjectInfo& GetInfo();

public:
	void SetID(size_t ID);
	void SetRenderID(size_t ID);
	void SetInfo(size_t ObjectID, RENDER_TYPE Type, size_t RenderID);

public:
	virtual void Initialize() 			PURE;
	virtual void InitState()			PURE;
	virtual void FixedUpdate(float dt)	PURE;
	virtual void Update(float dt)		PURE;
	virtual void LateUpdate(float dt)	PURE;

public:
	virtual void OnCollisionEnter(IObject* Other) PURE;
	virtual void OnCollisionExit(IObject* Other)  PURE;

public:
	IObject* Clone() override PURE;

private:
	virtual void RenderEnter() PURE;
	virtual void Render()	   PURE;
	virtual void RenderExit()  PURE;

protected:
	GameInstance* instance = nullptr;
	Transform* m_Transform = nullptr;
	StateMachine m_StateMachine;
private:
	ObjectInfo m_Info;
};
END