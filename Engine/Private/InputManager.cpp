#include "InputManager.h"

void InputManager::Update()
{
	std::memcpy(&m_PrevKey, &m_CurKey, sizeof(m_PrevKey));
	for(SHORT i = 0; i < VK_MAX; ++i)
		m_CurKey[i] = (GetKeyState(i) & 0x8000) != 0;
}

bool InputManager::GetKey(KeyCode Key) const
{
	return m_CurKey[Key];
}

bool InputManager::GetKeyDown(KeyCode Key) const
{
	return m_CurKey[Key] && !m_PrevKey[Key];
}

bool InputManager::GetKeyUp(KeyCode Key) const
{
	return !m_CurKey[Key] && m_PrevKey[Key];
}
