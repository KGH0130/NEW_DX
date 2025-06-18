#pragma once

namespace Engine
{
using LPDEVICE = LPDIRECT3DDEVICE9;
using Matrix = D3DXMATRIX;
using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;

static constexpr size_t MAX_OBJ = 64ull;
static constexpr size_t INVALID = ~0ull;

#define VEC_ZERO Vector3(0.f, 0.f, 0.f)
#define VEC2_ZERO Vector2(0.f, 0.f)
#define VEC_ONE  Vector3(1.f, 1.f, 1.f)
}