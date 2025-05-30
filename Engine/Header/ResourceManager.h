#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class IResource;

class DLL ResourceManager
{
public:
	~ResourceManager();

public:
	void RegisterResource(const std::string& Name, IResource* Ptr);
	IResource* GetResource(const std::string& Name);
	void Clear();
private:
	std::unordered_map<std::string, IResource*> m_ResourceMap;
};
END