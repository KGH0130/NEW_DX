#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class DLL ILoad
{
public:
	virtual ~ILoad() = default;

public:
	virtual void LOAD() PURE;
};
END