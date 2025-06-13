#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
struct DLL AABB
{
	AABB() = default;
	AABB(OBJECT_TYPE Type, IObject* Owner, const Vector3& Offset, const Vector3& HalfSize)
		: type(Type)
		, owner(Owner)
		, offset(Offset)
		, halfSize(HalfSize)
	{}

	void Update()
	{
		const Vector3 pos = transform->GetPosition();

		Min = pos + offset - halfSize;
		Max = pos + offset + halfSize;
	}

	OBJECT_TYPE type{};
	IObject* owner = nullptr;
	Transform* transform = nullptr;
	Vector3 offset;
	Vector3 Min, Max;
	Vector3 halfSize;
};
END