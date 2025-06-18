#pragma once
#include "Engine_Macro.h"
#include "Engine_Typedef.h"

BEGIN(Engine)
struct CameraInfo
{
	CameraInfo() = default;
	CameraInfo(size_t ID)
		: id(ID)
	{}

	size_t id = INVALID;
};
END