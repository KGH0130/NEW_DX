#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
struct GameInstance
{
public:
	GameInstance(LPDEVICE DEVICE)
		: Device(DEVICE)
		, Level(this)
		, Collider(DEVICE)
	{}

	LPDEVICE Device = nullptr;
	LevelManager Level;
	ObjectManager Object;
	ColliderManager Collider;
	ResourceManager Resource;
	InputManager Input;
};
END