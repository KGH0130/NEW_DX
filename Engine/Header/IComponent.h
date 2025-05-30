#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class DLL IComponent : public IClone
{
public:
	virtual ~IComponent() = default;

public:
	void Initialize() override PURE;
	IClone* Clone() override PURE;
	void Free() override PURE;
};
END