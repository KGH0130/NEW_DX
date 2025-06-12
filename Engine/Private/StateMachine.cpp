#include "StateMachine.h"

void StateMachine::InitState(IState* State)
{
	assert(State);
	m_CurState = State;
	m_CurState->Enter();
}

void StateMachine::ChangeState(IState* NextState)
{
	if(m_CurState == NextState) return;
	m_CurState->Exit();
	m_CurState = NextState;
	m_CurState->Enter();
}

void StateMachine::Update(float dt)
{
	if(!m_CurState) return;
	m_CurState->Update(dt);
}
