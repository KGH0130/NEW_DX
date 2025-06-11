#pragma once
#include "Engine_Macro.h"
#include "Engine_Typedef.h"
#include "Input_Enum.h"

BEGIN(Engine)
class DLL InputManager
{
public:
	void Update();
	bool GetKey(KeyCode Key) const;
	bool GetKeyDown(KeyCode Key) const;
	bool GetKeyUp(KeyCode Key) const;

private:
	static constexpr uint16_t VK_MAX = 256;
	bool m_PrevKey[VK_MAX]{}, m_CurKey[VK_MAX]{};
};
END