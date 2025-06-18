#pragma once

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
	CameraManager Camera;
	CollisionManager Collider;
	InputManager Input;
};
END