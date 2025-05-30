#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class DLL IClone
{
public:
	virtual ~IClone() = default;

public:
	virtual void Initialize()	PURE;
	virtual IClone* Clone()		PURE;
	virtual void Free()			PURE;
};
END