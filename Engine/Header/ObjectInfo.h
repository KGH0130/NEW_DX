#pragma once
#include "Engine_Macro.h"
#include "Engine_Typedef.h"

BEGIN(Engine)
struct ObjectInfo
{
	ObjectInfo() = default;
	ObjectInfo(size_t ObjectID, CREATE_TYPE CreateType, RENDER_TYPE RenderType, size_t RenderID)
		: objectID(ObjectID)
		, createType(CreateType)
		, renderType(RenderType)
		, renderID(RenderID)
	{}

	size_t objectID = INVALID;
	CREATE_TYPE createType{};

	RENDER_TYPE renderType{};
	size_t renderID = INVALID;
};
END