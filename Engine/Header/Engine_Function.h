#pragma once
#include "Engine_Typedef.h"

namespace Engine
{
template<typename T>
void SAFE_DELETE(T& Point) noexcept
{
	if(Point == nullptr) return;

	delete Point;
	Point = nullptr;
}

template<typename T>
void SAFE_DELETE_VEC(std::vector<T*>& Vec) noexcept
{
	for(auto& var : Vec)
	{
		SAFE_DELETE(var);
	}
	Vec.clear();
}

template<typename T>
T Clamp(T Value, T Min, T Max) noexcept
{
	if(Value < Min) return Min;
	if(Value > Max) return Max;
	return Value;
}

template<typename T>
T Lerp(T Start, T End, float Time) noexcept
{
	return Start + (End - Start) * Clamp(Time, 0.0f, 1.0f);
}

inline float Dot(const Vector3& Dst, const Vector3& Src) noexcept
{
	return Dst.x * Src.x + Dst.y * Src.y + Dst.z * Src.z;
}

}