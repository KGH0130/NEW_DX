#pragma once
#include "Engine_Macro.h"

struct DLL AABB
{
	AABB() = default;
	AABB(OBJECT_TYPE Type, const Vector3& Center, const Vector3& HalfSize)
		: type(Type)
		, Min(Center - HalfSize), Max(Center + HalfSize)
	{}

	void Update(const Vector3& Center, const Vector3& HalfSize)
	{
		this->Min = Center - HalfSize;
		this->Max = Center + HalfSize;
	}

	OBJECT_TYPE type;

	Vector3 Min;
	Vector3 Max;
};