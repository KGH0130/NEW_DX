

void Main_Level::Initialize()
{
	instance->Object.AddObject(RENDER_TYPE::NONE, "MainCamera");
}

void Main_Level::Loading()
{
	instance->Object.RegisterObject("Player", new Player(instance));
	instance->Object.RegisterObject("MainCamera", new MainCamera(instance));
}
