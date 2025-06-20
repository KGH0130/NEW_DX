#pragma once

namespace Engine
{
#pragma region DIRECT9
using LPDEVICE = LPDIRECT3DDEVICE9;
using Matrix = D3DXMATRIX;
using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;
#pragma endregion

#pragma region DIRECT11
using DEVICE = ID3D11Device*;
using CONTEXT = ID3D11DeviceContext*;

using vector2 = XMFLOAT2;
using vector3 = XMFLOAT3;
using vector4 = XMFLOAT4;
using matrix = XMFLOAT4X4;
#pragma endregion

static constexpr size_t MAX_OBJ = 64ull;
static constexpr size_t INVALID = ~0ull;

#define VEC_ZERO Vector3(0.f, 0.f, 0.f)
#define VEC2_ZERO Vector2(0.f, 0.f)
#define VEC_ONE  Vector3(1.f, 1.f, 1.f)
}