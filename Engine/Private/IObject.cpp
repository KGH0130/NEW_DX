#include "IObject.h"

IObject::IObject(GameInstance* Instance)
	: instance(Instance)
{}

void IObject::OnRender()
{
	RenderState();
	Render();
}