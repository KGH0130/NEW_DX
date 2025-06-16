#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
struct CollisionHash
{
	std::size_t operator()(const std::pair<IObject*, IObject*>& P) const noexcept
	{
		return std::hash<const IObject*>()(P.first) ^ std::hash<const IObject*>()(P.second);
	}
};
END