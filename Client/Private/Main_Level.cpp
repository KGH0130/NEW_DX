

void Main_Level::Initialize()
{
	instance->Object.AddObject(RENDER_TYPE::PRIORITY, "Player");
	instance->Object.AddObject(RENDER_TYPE::NONE, "MainCamera");
}

void Main_Level::Loading()
{
	instance->Object.RegisterObject("Player", new Player(instance), CREATE_TYPE::STATIC);
	instance->Object.RegisterObject("MainCamera", new MainCamera(instance), CREATE_TYPE::STATIC);
}
