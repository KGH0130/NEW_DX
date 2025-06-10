#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
struct GameInstance;

class ILevel
{
public:
	virtual ~ILevel() = default;

public:
	bool OnLoading(GameInstance* Instance);

private:
	virtual void Initialize() PURE;
	virtual void Loading() PURE;

protected:
	GameInstance* instance = nullptr;
};
END