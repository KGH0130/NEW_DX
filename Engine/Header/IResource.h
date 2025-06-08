#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class DLL IResource
{
public:
	IResource(LPDEVICE Device);
	virtual ~IResource() = default;

public:
	virtual void Render() PURE;

protected:
	LPDEVICE m_Device;
};
END