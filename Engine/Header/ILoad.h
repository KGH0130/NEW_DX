#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class DLL ILoad
{
public:
	virtual ~ILoad() = default;

public:
	virtual void Enter() PURE;
	virtual void LOAD() PURE;
	virtual void Exit() PURE;
};
END