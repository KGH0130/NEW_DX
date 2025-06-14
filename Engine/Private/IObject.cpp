#include "IObject.h"

IObject::IObject(GameInstance* Instance)
	: instance(Instance)
{}

void IObject::OnInitialize()
{}

void IObject::OnUpdate(float dt)
{}

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

void IObject::SetInfo(size_t ObjectID, RENDER_TYPE Type, size_t RenderID)
{
	m_Info = ObjectInfo(ObjectID, Type, RenderID);
}