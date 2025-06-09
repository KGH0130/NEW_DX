#include "IObject.h"

IObject::IObject(GameInstance* Instance)
	: instance(Instance)
	, m_Transform(instance->Component.CreateTransform())
{}

void IObject::OnRender()
{
	RenderEnter();
	Render();
	RenderExit();
}

const ObjectInfo& IObject::GetInfo()
{
	return m_Info;
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