#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class DLL IClone
{
public:
	virtual ~IClone() = default;

public:
	virtual IClone* Clone()	PURE;
};
END