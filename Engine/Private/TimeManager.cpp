#include "TimeManager.h"

TimeManager::TimeManager(int F, int U)
	: m_LimitF(1.f / static_cast<float>(F)), m_LimitU(1.f / static_cast<float>(U))
{
	QueryPerformanceFrequency(&m_Frequency);
	QueryPerformanceCounter(&m_PrevTime);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&m_CurTime);
	m_Dt = static_cast<float>(m_CurTime.QuadPart - m_PrevTime.QuadPart) / static_cast<float>(m_Frequency.QuadPart);
	m_PrevTime = m_CurTime;
	m_AccF += m_Dt;
	m_AccU += m_Dt;
	m_AccI += m_Dt;
	++m_Fps;
}

bool TimeManager::FixedLimit()
{
	if(m_AccF >= m_LimitF)
	{
		m_AccF -= m_LimitF;
		return true;
	}
	return false;
}

bool TimeManager::UpdateLimit()
{
	if(m_AccU >= m_LimitU)
	{
		m_AccU -= m_LimitU;
		return true;
	}
	return false;
}

void TimeManager::FPS_INFO(HWND hWnd)
{
	if(m_AccI >= 1.f)
	{
		m_AccI -= 1.f;
		wchar_t title[64];
		swprintf_s(title, L"FPS: %d", m_Fps);
		SetWindowTextW(hWnd, title);
		m_Fps = 0;
	}
}

float TimeManager::GetDT() const
{
	return m_Dt;
}

float TimeManager::GetFDT() const
{
	return m_LimitF;
}