#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class ILevel
{
public:
	virtual ~ILevel() = default;

public:
	void OnLoading(GameInstance* Instance);

private:
	virtual void Initialize() PURE;
	virtual void Loading() PURE;

protected:
	GameInstance* instance = nullptr;
};
END