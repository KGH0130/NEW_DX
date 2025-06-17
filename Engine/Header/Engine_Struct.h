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

struct VTX_DESC
{
	VTX_DESC() = default;
	VTX_DESC(uint32_t VTXCount, uint32_t Stride, D3DPRIMITIVETYPE Type, uint32_t PrimitiveCount)
		: vertexCount(VTXCount), stride(Stride)
		, primitiveType(Type)
		, primitiveCount(PrimitiveCount)
	{}

	uint32_t vertexCount = 0u;
	uint32_t stride = 0u;
	D3DPRIMITIVETYPE primitiveType{};
	uint32_t primitiveCount = 0u;
};

struct IDX_DESC
{
	IDX_DESC() = default;
	IDX_DESC(uint32_t IndexCount, D3DFORMAT Format)
		: indexCount(IndexCount)
		, indexFormat(Format)
	{
		stride = indexFormat == D3DFORMAT::D3DFMT_INDEX16 ? sizeof(int16_t) : sizeof(int32_t);
	}

	uint32_t indexCount = 0u;
	D3DFORMAT indexFormat{};
	uint32_t stride = 0u;
};

struct COLLIDER_VTX
{
	Vector3 pos;
	DWORD color;
};
static constexpr auto D3DFVF_COLLIDER = (D3DFVF_XYZ | D3DFVF_DIFFUSE);

}