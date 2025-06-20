#pragma once
#include "Engine_Typedef.h"

namespace Engine
{
struct GRAPHIC_DESC
{
	GRAPHIC_DESC(HWND Hwnd, bool Windowed, uint32_t Wincx, uint32_t Wincy)
		: hwnd(Hwnd)
		, windowed(Windowed)
		, wincx(Wincx), wincy(Wincy)
	{}

	HWND hwnd = nullptr;
	bool windowed = true;
	uint32_t wincx = 0u, wincy = 0u;
};

struct DEVICE_REF
{
	DEVICE_REF() = default;
	DEVICE_REF(DEVICE Device, CONTEXT Context)
		: device(Device)
		, context(Context)
	{}

	DEVICE device = nullptr;
	CONTEXT context = nullptr;
};

struct COLLIDER_VTX
{
	Vector3 pos;
	DWORD color;
};
constexpr auto D3DFVF_COLLIDER = (D3DFVF_XYZ | D3DFVF_DIFFUSE);

}