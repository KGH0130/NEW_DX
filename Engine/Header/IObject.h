#pragma once
#include "Engine_Macro.h"
#include "ObjectInfo.h"
#include "Transform.h"

BEGIN(Engine)
class Collider;
struct GameInstance;

class DLL IObject : public IClone
{
public:
	IObject(GameInstance* Instance);
	virtual ~IObject() = default;

public:
	virtual void OnInitialize()		PURE;
	virtual void OnUpdate(float dt) PURE;
	void OnRender();

public:
	const ObjectInfo& GetInfo() const;
	const Transform& GetTransform() const;

public:
	void SetID(size_t ID);
	void SetRenderID(size_t ID);
	void SetInfo(size_t ObjectID, RENDER_TYPE Type, size_t RenderID);

public:
	virtual void Initialize() 			PURE;
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
	Collider* m_Collider = nullptr;

protected:
	Transform m_Transform;
private:
	ObjectInfo m_Info;
};
END