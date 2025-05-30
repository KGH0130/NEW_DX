#pragma once
#include "Engine_Macro.h"
#include "Engine_Typedef.h"

BEGIN(Engine)
class DLL Graphic_Device
{
public:
	Graphic_Device(const GRAPHIC_DESC& Desc) noexcept;

public:
	LPDEVICE GetDevice() const noexcept;

private:
	LPDIRECT3D9 m_SDK;
	LPDEVICE m_Device;
};
END