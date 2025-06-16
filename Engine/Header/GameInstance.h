#pragma once
#include "Engine_Macro.h"

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
	CollisionManager Collider;
	ResourceManager Resource;
	InputManager Input;
};
END