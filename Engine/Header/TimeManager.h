#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class DLL TimeManager
{
public:
	TimeManager(int F, int U);

public:
	void Update();

	bool FixedLimit();
	bool UpdateLimit();

	void FPS_INFO(HWND hWnd);

	float GetDT() const;
	float GetFDT() const;

private:
	LARGE_INTEGER m_Frequency{};
	LARGE_INTEGER m_PrevTime{}, m_CurTime{};

	float m_Dt = 0.f, m_AccFixed = 0.f, m_AccUpdate = 0.f, m_AccInfo = 0.f;
	float m_LimitF = 0.f, m_LimitU = 0.f;
	int m_Fps = 0;
};
END