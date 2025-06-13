#pragma once
#include "Engine_Enum.h"
#include "Engine_Macro.h"

BEGIN(Engine)
struct ColliderInfo
{
	ColliderInfo() = default;
	ColliderInfo(size_t ID, COLLISION_TYPE CollType, OBJECT_TYPE ObjType)
		: id(ID)
		, collType(CollType)
		, objType(ObjType)
	{}

	size_t id = INVALID;
	COLLISION_TYPE collType{};
	OBJECT_TYPE objType{};
};
END