#include "Entity.h"

Entity::Entity(GameInstance* Instance)
	: IObject(Instance)
	, m_Rigid(m_Transform)
{}

void Entity::OnInitialize()
{
	Initialize();
	InitState();
}

void Entity::OnUpdate(float dt)
{
	m_StateMachine.Update(dt);
	Update(dt);
	m_Rigid.Update(dt);
	m_Transform.UpdateMatrix();
}