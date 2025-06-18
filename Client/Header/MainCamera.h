#pragma once

class MainCamera : public ICamera
{
public:
	MainCamera(GameInstance* Instance);

private:
	void Initialize() override;
	void LateUpdate(float dt) override;

private:
	ICamera* Clone() override;
};