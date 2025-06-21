#pragma once
#include "Engine_Enum.h"
#include "Engine_Macro.h"

BEGIN(Engine)
struct ColliderInfo
{
	ColliderInfo() = default;
	ColliderInfo(size_t ID, OBJECT_TYPE ObjType)
		: id(ID)
		, objType(ObjType)
		, collType(COLLISION_TYPE::DYNAMIC)

	{}
	ColliderInfo(size_t ID, REGION_TYPE RegionType)
		: id(ID)
		, regiontype(RegionType)
		, collType(COLLISION_TYPE::STATIC)

	{}

	size_t id = INVALID;
	OBJECT_TYPE objType{};
	REGION_TYPE regiontype{};
	COLLISION_TYPE collType{};
};
END