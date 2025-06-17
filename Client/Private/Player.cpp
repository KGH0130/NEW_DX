#include "Player.h"

Player::Player(GameInstance* Instance)
	: Entity(Instance)
{}

void Player::Initialize()
{
	m_Collider = instance->Collider.AddCollider(this, COLLISION_TYPE::DYNAMIC, OBJECT_TYPE::PLAYER);
	m_Collider->CreateAABB(VEC_ZERO, Vector3(1.f, 1.f, 1.f));
	m_Collider->CreateOBB(VEC_ZERO);
	m_Rigid.SetGravity(false);
}

void Player::InitState()
{}

void Player::FixedUpdate(float dt)
{}

void Player::Update(float dt)
{
	Move();
}

void Player::LateUpdate(float dt)
{}

void Player::RenderEnter()
{
	instance->Device->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void Player::Render()
{}

void Player::RenderExit()
{}

void Player::OnCollisionEnter(IObject* Other)
{}

void Player::OnCollisionExit(IObject* Other)
{}

IObject* Player::Clone()
{
	return new Player(instance);
}

void Player::Move()
{

}
