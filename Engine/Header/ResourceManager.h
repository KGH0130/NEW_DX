#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class IResource;

class DLL ResourceManager
{
public:
	~ResourceManager();

public:
	void RegisterResource(const std::string& Name, IResource* Resource);
	IResource* GetResoucre(const std::string& Name);

private:
	std::unordered_map<std::string, IResource*> m_ResourceMap;
};
END