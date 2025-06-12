#pragma once
#include "AABB.h"
#include "Engine_Enum.h"
#include "Engine_Macro.h"

BEGIN(Engine)
class DLL ColliderManager
{
public:
	~ColliderManager() = default;

public:
	void Update();


private:
	std::array<std::vector<AABB>, static_cast<size_t>(OBJECT_TYPE::IDX)> m_AABB{};

};
END