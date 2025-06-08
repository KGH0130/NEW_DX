#pragma once
#include "Engine_Macro.h"
#include "Engine_Typedef.h"

BEGIN(Engine)
struct ObjectInfo
{
	ObjectInfo() = default;
	ObjectInfo(size_t ObjectID, RENDER_TYPE Type, size_t RenderID)
		: objectID(ObjectID)
		, type(Type)
		, renderID(RenderID)
	{}

	size_t objectID = INVALID;
	size_t renderID = INVALID;

	RENDER_TYPE type{};
};
END