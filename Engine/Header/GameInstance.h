#pragma once

BEGIN(Engine)
struct GameInstance
{
public:
	GameInstance(LPDEVICE DEVICE)
		: Device(DEVICE)
		, Level(this)
		, Component(Object)
	{}

	LPDEVICE Device = nullptr;
	LevelManager Level;
	ObjectManager Object;
	ComponentManager Component;
	ResourceManager Resource;
	InputManager Input;
};
END