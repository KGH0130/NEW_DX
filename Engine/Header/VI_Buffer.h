#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class DLL VI_Buffer : public IResource
{
public:
	VI_Buffer(LPDEVICE Device);

public:
	void Render() override;
};
END