#pragma once
#include "ComponentManager.h"
#include "Engine_Macro.h"
#include "Engine_Typedef.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include "ResourceManager.h"

BEGIN(Engine)
struct GameInstance
{
public:
	GameInstance(LPDEVICE DEVICE)
		: Device(DEVICE)
		, Level(this)
	{}

	LPDEVICE Device = nullptr;
	LevelManager Level;
	ObjectManager Object;
	ComponentManager Component;
	ResourceManager Resource;
	InputManager Input;
};
END