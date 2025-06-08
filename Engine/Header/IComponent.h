#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class DLL IComponent
{
public:
	virtual ~IComponent() = default;
};
END