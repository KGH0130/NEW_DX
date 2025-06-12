#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class StateMachine;

class IState
{
public:
	IState(StateMachine& Machine);
	virtual ~IState() = default;

public:
	virtual void Enter()			PURE;
	virtual void Update(float dt)	PURE;
	virtual void Exit()				PURE;

protected:
	StateMachine& machine;
};
END