#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class ICamera;
class IObject;

class DLL CameraManager
{
public:
	~CameraManager();

public:
	void Register(const std::string& Name, ICamera* Camera);
	ICamera* Init(const std::string& Name, IObject* Target);
	ICamera* Get(const std::string& Name);
	void Release(const ICamera* Camera);

public:
	void LateUpdate(float dt);

public:
	void Flush();

private:
	void AddPending();
	void RemovePending();

private:
	std::unordered_map<std::string, ICamera*> m_CameraMap;
	std::unordered_map<std::string, ICamera*> m_CloneMap;

	std::vector<ICamera*> m_AddPending;
	std::vector<size_t> m_RemovePending;

	std::vector<ICamera*> m_Cameras;
};
END