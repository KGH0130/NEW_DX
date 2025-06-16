#include "IObject.h"

IObject::IObject(GameInstance* Instance)
	: instance(Instance)
{}

void IObject::OnInitialize()
{
	Initialize();
}

void IObject::OnUpdate(float dt)
{
	Update(dt);
}

void IObject::OnRender()
{
	RenderEnter();
	Render();
	RenderExit();
}

const ObjectInfo& IObject::GetInfo() const
{
	return m_Info;
}

Transform& IObject::GetTransform()
{
	return m_Transform;
}

void IObject::SetID(size_t ID)
{
	m_Info.objectID = ID;
}

void IObject::SetRenderID(size_t ID)
{
	m_Info.renderID = ID;
}

void IObject::SetInfo(size_t ObjectID, CREATE_TYPE CreateType, RENDER_TYPE RenderType, size_t RenderID)
{
	m_Info = ObjectInfo(ObjectID, CreateType, RenderType, RenderID);
}