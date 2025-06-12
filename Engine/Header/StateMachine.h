#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class IState;

class DLL StateMachine
{
public:
	void InitState(IState* State);
	void ChangeState(IState* NextState);
	void Update(float dt);

private:
	IState* m_CurState = nullptr;
};

END