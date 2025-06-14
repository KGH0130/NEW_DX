#include "Entity.h"

Entity::Entity(GameInstance* Instance)
	: IObject(Instance)
{}

void Entity::OnUpdate(float dt)
{
	Update(dt);
	m_StateMachine.Update(dt);
	m_Transform.UpdateMatrix();
}

void Entity::OnInitialize()
{
	Initialize();
	InitState();
}